#include <Cad3d_Solid.hxx>

#include <GeoProcessor.hxx>
#include <Entity3d_Box.hxx>
#include <Entity3d_Chain.hxx>
#include <Merge3d_Chain.hxx>
#include <Solid_Vertex.hxx>
#include <Solid_Edge.hxx>
#include <Solid_Ring.hxx>
#include <Solid_Curve.hxx>
#include <Solid_EntityManager.hxx>
#include <Solid_BlockEntity.hxx>
#include <Solid_Entity.hxx>
#include <Solid_Paired.hxx>
#include <Solid_Face.hxx>
#include <Cad3d_SolidTools.hxx>

#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepExtrema_ExtCC.hxx>

namespace AutLib
{

	typedef std::shared_ptr<Solid_Edge> edge_ptr;
	typedef std::vector<edge_ptr> edgeList;

	typedef Entity3d_Chain chain3;
	typedef std::shared_ptr<Solid_EntityManager> entityManager_ptr;
	typedef std::shared_ptr<Solid_Entity> entity_ptr;
	typedef std::vector<entity_ptr> entityList;
	typedef std::shared_ptr<Solid_Vertex> vertex_ptr;
	typedef std::shared_ptr<Solid_Face> face_ptr;
	typedef std::vector<face_ptr> faceList;

	TopoDS_Edge MakeEdge
	(
		const Handle(Geom_Curve)& theCurve,
		const Standard_Real p0,
		const Standard_Real p1
	)
	{
		return BRepBuilderAPI_MakeEdge(theCurve, p0, p1);
	}

	Standard_Real squareMaxDistance
	(
		const edge_ptr& theEdge0,
		const edge_ptr& theEdge1
	)
	{
		Debug_Null_Pointer(theEdge0->Geometry());
		Debug_Null_Pointer(theEdge1->Geometry());

		auto edge0 = theEdge0->TEdge();
		auto edge1 = theEdge1->TEdge();

		BRepExtrema_ExtCC dist(edge0, edge1);
		
		if (!dist.IsDone())
		{
			FatalErrorIn("Standard_Real MaxDistance(const edge_ptr& theEdge0, const edge_ptr& theEdge1)")
				<< "Failed to find extremas!" << endl
				<< abort(FatalError);
		}

		if (!dist.NbExt())
		{
			FatalErrorIn("Standard_Real MaxDistance(const edge_ptr& theEdge0, const edge_ptr& theEdge1)")
				<< "Failed to find extremas!" << endl
				<< " - NbExt = " << dist.NbExt() << endl
				<< abort(FatalError);
		}

		auto MaxDist = RealFirst();
		forThose(Index, 1, dist.NbExt())
		{
			cout << "dis = " << dist.SquareDistance(Index) << std::endl;
			cout << "param = " << dist.ParameterOnE1(Index) << std::endl;
			MaxDist = Max(MaxDist, dist.SquareDistance(Index));
		}

		return MaxDist;
	}

	Standard_Real squareMaxDistance_1
	(
		const edge_ptr& theEdge0,
		const edge_ptr& theEdge1
	)
	{
		Debug_Null_Pointer(theEdge0->Geometry());
		Debug_Null_Pointer(theEdge1->Geometry());

		const auto& geometry0 = *theEdge0->Geometry();
		const auto& geometry1 = *theEdge1->Geometry();

		return SquareDistance(geometry0.NormalizedParameterValue(0.5), geometry1.NormalizedParameterValue(0.5));
	}

	static void MakeStaticChain
	(
		const edgeList& Edges,
		Entity3d_Chain& Chain
	)
	{
		auto& Points = Chain.Points();
		auto& Indices = Chain.Connectivity();

		Points.resize(2 * Edges.size());
		Indices.reserve(Edges.size());

		Standard_Integer IP = 0;
		for (const auto& x : Edges)
		{
			Debug_Null_Pointer(x);
			Debug_Null_Pointer(x->Geometry());

			const auto& curve = *x->Geometry();

			Points[IP] = curve.Start();
			IP++;

			Points[IP] = curve.Last();
			IP++;

			connectivity::dual edge;
			edge.Value(0) = IP - 1;
			edge.Value(1) = IP;

			Indices.push_back(edge);
		}
	}

	static void MakePointsOnSolid
	(
		const chain3& Chain,
		entityManager_ptr& thePointsOnSolid,
		entityList& thePts
	)
	{
		const auto& Points = Chain.Points();

		thePts.resize(Points.size());
		forThose(Index, 0, thePts.size() - 1)
		{
			thePts[Index] = std::make_shared<Solid_Vertex>(Index + 1, Points[Index]);
		}

		auto block = std::make_shared<Solid_BlockEntity>("Default Block Point", thePts);
		thePointsOnSolid = std::make_shared<Solid_EntityManager>("Default Block Point", block);
	}

	static void Pairing(const edgeList& theEdges)
	{
		if (theEdges.size() < 2)
		{
			FatalErrorIn("void Pairing(const edgeList& theEdges)")
				<< "Invalid Solid" << endl
				<< abort(FatalError);
		}

		Adt_AvlTree<edge_ptr> tree;
		tree.SetComparableFunction(&Solid_Edge::IsLess);

		for (const auto& x : theEdges)
			tree.Insert(x);
		Debug_If_Condition(tree.IsEmpty());

		edge_ptr edge;
		tree.Root(edge);
		tree.Remove(edge);

		while (NOT tree.IsEmpty())
		{
			const auto& vtx0 = edge->Start();
			const auto& vtx1 = edge->End();
			
			vertex_ptr vtx;
			if (vtx0->NbEdges() <= vtx1->NbEdges())
				vtx = vtx0;
			else
				vtx = vtx1;

			std::vector<std::weak_ptr<Solid_Edge>> compareList;
			vtx->RetrieveEdgesTo(compareList);

			auto v0 = vtx0->Index();
			auto v1 = vtx1->Index();

			auto ring = std::dynamic_pointer_cast<Solid_Ring>(edge);
			if (ring)
			{
				auto tol2 = ring->Presicion()*ring->Presicion();

				for (const auto& w_compare : compareList)
				{
					auto compare = w_compare.lock();
					Debug_Null_Pointer(compare);

					if (compare IS_EQUAL edge) continue;

					auto compareRing = std::dynamic_pointer_cast<Solid_Ring>(compare);
					if (compareRing)
					{
						if (squareMaxDistance_1(ring, compareRing) <= tol2)
						{
							edge->SetPairedEdge(compare);
							compare->SetPairedEdge(edge);

							tree.Remove(compare);
						}
					}
				}
			}
			else
			{
				edgeList paired;

				Debug_Null_Pointer(edge->Geometry());
				auto tol2 = edge->Presicion()*edge->Presicion();

				for (const auto& w_compare : compareList)
				{
					auto compare = w_compare.lock();
					Debug_Null_Pointer(compare);

					if (compare IS_EQUAL edge) continue;

					if (Processor::IsPairedTwoSegments(v0, v1, compare->Start()->Index(), compare->End()->Index()))
					{
						if (squareMaxDistance_1(edge, compare) <= tol2)
						{
							paired.push_back(compare);
						}

						//paired.push_back(compare);
					}
				}

				/*if (paired.empty())
				{
					cout << "nothing found!" << std::endl;
				}*/
				if (paired.size() > 1)
				{
					if (edge->PairedEdge().lock())
					{
						FatalErrorIn("void Pairing(const edgeList& theEdges)")
							<< "the solid is not a manifold type"
							<< abort(FatalError);
					}
				}

				if (paired.size() IS_EQUAL 1)
				{
					edge->SetPairedEdge(paired[0]);
					paired[0]->SetPairedEdge(edge);
				}
			}

			if (tree.IsEmpty()) break;

			tree.Root(edge);
			tree.Remove(edge);
		}
	}

	static void Assembly
	(
		const chain3& theChain, 
		const entityList& Vertices,
		const edgeList& Edges
	)
	{
		const auto& Indices = theChain.Connectivity();
		if (Edges.size() NOT_EQUAL Indices.size())
		{
			FatalErrorIn("void Assembly()")
				<< "Contradictory Data"
				<< abort(FatalError);
		}

		forThose
		(
			Index,
			0,
			Indices.size() - 1
		)
		{
			auto v0 = Indices[Index].Value(0);
			auto v1 = Indices[Index].Value(1);

			auto vtx0 = std::dynamic_pointer_cast<Solid_Vertex>(Vertices[Index_Of(v0)]);
			auto vtx1 = std::dynamic_pointer_cast<Solid_Vertex>(Vertices[Index_Of(v1)]);

			Debug_Null_Pointer(vtx0);
			Debug_Null_Pointer(vtx1);

			Debug_Null_Pointer(Edges[Index]);

			Edges[Index]->Start() = vtx0;
			Edges[Index]->End() = vtx1;

			Edges[Index]->SetIndex(Index + 1);

			if (v0 IS_EQUAL v1)
			{
				//! For ring configuration
				vtx0->ImportToEdges(Edges[Index]);
			}
			else
			{
				vtx0->ImportToEdges(Edges[Index]);
				vtx1->ImportToEdges(Edges[Index]);
			}
		}

		Pairing(Edges);

		for (const auto& x : Vertices)
		{
			Debug_Null_Pointer(x);

			auto vertex = std::dynamic_pointer_cast<Solid_Vertex>(x);
			Debug_Null_Pointer(vertex);

			std::vector<std::weak_ptr<Solid_Edge>> edgesAroundVertex;
			vertex->RetrieveEdgesTo(edgesAroundVertex);

			for (const auto& edge : edgesAroundVertex)
			{
				Debug_Null_Pointer(edge.lock());
				vertex->ImportToFaces_dup(edge.lock()->Face());
			}
		}
	}

	static void MakePairedEdges
	(
		const edgeList& theEdges,
		entityManager_ptr& PairedEdges
	)
	{
		Adt_AvlTree<edge_ptr> tree;
		tree.SetComparableFunction(&Solid_Edge::IsLess);

		tree.Insert(theEdges);

		edge_ptr edge;
		tree.Root(edge);
		tree.Remove(edge);

		entityList QPaired;
		Standard_Integer k = 0;

		while (NOT tree.IsEmpty())
		{
			auto w_paired = edge->PairedEdge();
			auto paired = w_paired.lock();

			if (paired)
			{
				tree.Remove(paired);
			}

			auto pairedOnSolid = std::make_shared<Solid_Paired>(++k, edge, paired);
			QPaired.push_back(pairedOnSolid);

			edge->SetPaired(pairedOnSolid);
			if (paired) paired->SetPaired(pairedOnSolid);

			if (tree.IsEmpty()) break;

			tree.Root(edge);
			tree.Remove(edge);
		}

		auto block = std::make_shared<Solid_BlockEntity>("Default Block Edge", QPaired);
		PairedEdges = std::make_shared<Solid_EntityManager>("Default Block Edge", block);
	}

	static void MarchingOnShell
	(
		const face_ptr& Face,
		Adt_AvlTree<face_ptr>& tree,
		entityList& QShell
	)
	{
		tree.Remove(Face);
		QShell.push_back(Face);

		const auto edges = Face->Edges();

		edgeList pairedList;
		pairedList.reserve(edges.size());

		edge_ptr null = nullptr;

		for (const auto& x : edges)
		{
			Debug_Null_Pointer(x);

			pairedList.push_back(x->PairedEdge().lock());
			x->SetPairedEdge(null);
		}

		for (const auto& x : pairedList)
		{
			if (x)
			{
				auto paired = x->PairedEdge().lock();
				if (paired)
				{
					Debug_Null_Pointer(paired->Face().lock());
					MarchingOnShell(paired->Face().lock(), tree, QShell);
				}
			}
		}
	}

	static void MakeFaces
	(
		const faceList& theList,
		entityManager_ptr& theFaces
	)
	{
		entityList Faces(theList.size());
		forThose(Index, 0, theList.size() - 1)
			Faces[Index] = theList[Index];

		auto block = std::make_shared<Solid_BlockEntity>("Default Block Surface", Faces);
		theFaces = std::make_shared<Solid_EntityManager>("Default Block Surface", block);
	}

	static void LinkEdges(const entityManager_ptr& theEdges)
	{
		Debug_Null_Pointer(theEdges);

		entityList edges;
		theEdges->RetrieveTo(edges);

		for (const auto& x : edges)
		{
			Debug_Null_Pointer(x);
			
			auto paired = std::dynamic_pointer_cast<Solid_Paired>(x);
			Debug_Null_Pointer(paired);

			auto edge0 = paired->Edge0();
			auto edge1 = paired->Edge1();

			if (NOT edge0)
			{
				FatalErrorIn("void LinkEdges(const entityManager_ptr& theEdges)")
					<< "Null pointer has been encountered!" << endl
					<< abort(FatalError);
			}

			if (edge1)
			{
				edge0->SetPairedEdge(edge1);
				edge1->SetPairedEdge(edge0);
			}
		}
	}
}

void AutLib::Cad3d_Solid::Make
(
	const faceList & theFaces
)
{
	CalcBoundingBox(theFaces);
	Debug_Null_Pointer(theBoundingBox_);

	const auto tol = Tolerance * theBoundingBox_->Diameter();
	auto EdgesOnSolid = Cad3d_SolidTools::RetrieveNonDegeneratedEdges(theFaces);

	Standard_Integer K = 0;
	for (auto& x : EdgesOnSolid)
	{
		x->SetIndex(++K);
		x->SetPrecision(tol);
	}
	
	Entity3d_Chain Chain;
	MakeStaticChain(EdgesOnSolid, Chain);

	Merge3d_Chain merge;
	merge.InfoAlg().SetRadius(tol);
	merge.Import(Chain);

	merge.Perform();
	
	const auto& merged = *merge.Merged();

	entityList vertexList;
	MakePointsOnSolid(merged, theVertices_, vertexList);
	
	Debug_Null_Pointer(theVertices_);

	K = 0;
	for (auto& x : vertexList)
		x->SetIndex(++K);
	
	Assembly(merged, vertexList, EdgesOnSolid);
	
	MakePairedEdges(EdgesOnSolid, theEdges_);
	
	Debug_Null_Pointer(theEdges_);

	MakeFaces(theFaces, theFaces_);

	LinkEdges(theEdges_);

	if (NOT MakeShells(theFaces))
	{
		SplitByShells();
	}
}