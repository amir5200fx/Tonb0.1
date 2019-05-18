#include <Cad3d_SolidTools.hxx>

#include <Pnt2d.hxx>
#include <Pnt3d.hxx>
#include <Adt_AvlTree.hxx>
#include <Geom_AdTree.hxx>
#include <Entity3d_Box.hxx>
#include <Solid_Vertex.hxx>
#include <Solid_Curve.hxx>
#include <Solid_Edge.hxx>
#include <Solid_Paired.hxx>
#include <Solid_Face.hxx>
#include <Solid_parCurve.hxx>
#include <Solid_Plane.hxx>
#include <IO_IGES.hxx>

#include <IGESControl_Controller.hxx>
#include <IGESControl_Writer.hxx>
#include <GeomAPI_ProjectPointOnCurve.hxx>
#include <GeomAPI_ProjectPointOnSurf.hxx>
#include <Geom2dAPI_ProjectPointOnCurve.hxx>

namespace AutLib
{

	typedef std::shared_ptr<Solid_Vertex> vertex_ptr;
	typedef Adt_AvlTree<vertex_ptr> vertexRegister;
	typedef std::vector<Standard_Real> realList;
	typedef Geom_AdTree<vertex_ptr> geoEngine;
	typedef std::shared_ptr<Solid_Face> face_ptr;
	typedef std::vector<face_ptr> faceList;
	typedef std::shared_ptr<Solid_Paired> paired_ptr;
	typedef std::vector<paired_ptr> pairedList;
	typedef std::shared_ptr<Solid_Edge> edge_ptr;
	typedef std::vector<edge_ptr> edgeList;

	static void SplitParameters
	(
		const Solid_Edge& theEdge,
		const geoEngine& theEngine,
		realList& Parameters
	)
	{
		Debug_Null_Pointer(theEdge.Geometry());
		const auto& geometry = theEdge.Geometry();

		const auto gTol = theEdge.Presicion();
		
		const auto region = geometry->BoundingBox(gTol);

		std::vector<vertex_ptr> Found;
		theEngine.GeometrySearch(region, Found);
		
		const auto& curve = geometry->Curve();

		GeomAPI_ProjectPointOnCurve Projection;
		Projection.Init(curve, geometry->FirstParameter(), geometry->LastParameter());

		const auto P0 = geometry->Start();
		const auto P1 = geometry->Last();

		const auto vTol0 = theEdge.Start()->Presicion();
		const auto vTol1 = theEdge.End()->Presicion();

		for (const auto& x : Found)
		{
			Debug_Null_Pointer(x);

			const auto& vertex = *x;

			if (Distance(vertex.Coord(), P0) <= vTol0) continue;
			if (Distance(vertex.Coord(), P1) <= vTol1) continue;

			Projection.Perform(vertex.Coord());

#if MESH_DEBUG
			if (NOT Projection.NbPoints())
			{
				FatalErrorIn("void SplitParameters(const Solid_Edge& theEdge, geoEngine& theEngine, realList& Parameters)")
					<< "Failed to project the point on the curve" << endl
					<< abort(FatalError);
			}
#endif

			if (NOT Projection.NbPoints()) continue;

			if (Projection.LowerDistance() <= gTol)
			{
				Parameters.push_back(Projection.LowerDistanceParameter());
			}
		}

		if (Parameters.size() > 1)
		{
			std::sort(Parameters.begin(), Parameters.end());
		}
	}

	static void CalcParametersOfPlaneCurve
	(
		const Solid_Edge& theEdge,
		const realList& theParameters,
		realList& parameters
	)
	{
		Debug_Null_Pointer(theEdge.Geometry());
		Debug_Null_Pointer(theEdge.Par());
		Debug_Null_Pointer(theEdge.Par());
		Debug_Null_Pointer(theEdge.Face().lock());

		const auto& curve = theEdge.Geometry();
		const auto& pCurve = *theEdge.Par();
		const auto& surface = theEdge.Face().lock()->Geometry();

		std::vector<Pnt3d> Pts(theParameters.size());
		for (int i = 0; i < Pts.size(); i++)
		{
			Pts[i] = curve->Value(theParameters[i]);
		}

		Standard_Real Umin, Umax, Vmin, Vmax;
		surface->Bounds(Umin, Umax, Vmin, Vmax);

		GeomAPI_ProjectPointOnSurf SurfProjection;
		SurfProjection.Init(surface, Umin, Umax, Vmin, Vmax);

		std::vector<Pnt2d> pPts(Pts.size());
		for (int i = 0; i < Pts.size(); i++)
		{
			SurfProjection.Perform(Pts[i]);
			
#if MESH_DEBUG
			if (NOT SurfProjection.NbPoints())
			{
				FatalErrorIn("void CalcParametersOfPlaneCurve(const Solid_Edge& theSolid, const realList& theParameters, realList& parameters)")
					<< "Failed to project the point on the surface" << endl
					<< abort(FatalError);
			}
#endif

			SurfProjection.LowerDistanceParameters(pPts[i].X(), pPts[i].Y());
		}

		Geom2dAPI_ProjectPointOnCurve CurveProjection;
		parameters.reserve(pPts.size());

		for (const auto& x : pPts)
		{
			CurveProjection.Init(x, pCurve.Curve(), pCurve.FirstParameter(), pCurve.LastParameter());

#if MESH_DEBUG
			if (NOT CurveProjection.NbPoints())
			{
				FatalErrorIn("void CalcParametersOfPlaneCurve(const Solid_Edge& theSolid, const realList& theParameters, realList& parameters)")
					<< "Failed to project the point on the curve" << endl
					<< abort(FatalError);
			}
#endif

			if (NOT CurveProjection.NbPoints()) continue;
			parameters.push_back(CurveProjection.LowerDistanceParameter());
		}

		std::sort(parameters.begin(), parameters.end());
	}

	/*static std::shared_ptr<Solid_Edge> Copy(const Solid_Edge& theEdge)
	{
		Debug_Null_Pointer(theEdge.Geometry());
		Debug_Null_Pointer(theEdge.Par());


	}*/

	static edgeList SubdivideEdge
	(
		const Solid_Edge& theEdge,
		const realList& theParams2,
		const realList& theParams3
	)
	{
		if (theParams2.size() NOT_EQUAL theParams3.size())
		{
			FatalErrorIn("edgeList SubdivideEdge(const Solid_Edge& theEdge, const realList& theParams2, const realList& theParams3)")
				<< "Contradictory data!" << endl
				<< " - size of 2d parameter list = " << (label)theParams2.size() << endl
				<< " - size of 3d parameter list = " << (label)theParams3.size() << endl
				<< abort(FatalError);
		}

		Debug_Null_Pointer(theEdge.Par());
		Debug_Null_Pointer(theEdge.Face().lock());

		const auto& pCurve = theEdge.Par();
		const auto& Curve = theEdge.Geometry();

		Debug_Null_Pointer(pCurve);
		Debug_Null_Pointer(Curve);

		realList params2, params3;
		params2.reserve(theParams2.size() + 2);
		params3.reserve(theParams3.size() + 2);

		params2.push_back(pCurve->FirstParameter());
		params3.push_back(Curve->FirstParameter());

		for (const auto x : theParams2) params2.push_back(x);
		for (const auto x : theParams3) params3.push_back(x);

		params2.push_back(pCurve->LastParameter());
		params3.push_back(Curve->LastParameter());

		edgeList Edges(params2.size() + 1);
		for (int i = 0; i < Edges.size(); i++)
		{
			auto curveOnPlane = std::make_shared<Solid_parCurve>(params2[i], params2[i + 1], pCurve->Curve());
			auto curveOnSurface = std::make_shared<Solid_Curve>(params3[i], params3[i + 1], Curve->Curve());

			Edges[i] = std::make_shared<Solid_Edge>(0, curveOnSurface);
			Edges[i]->SetPar(curveOnPlane);
		}
		return std::move(Edges);
	}

	/*static face_ptr ModifiedPatch(const Solid_Face& theFace, const geoEngine& theEngine)
	{
		Debug_Null_Pointer(theFace.Edges());
		const auto& edges = *theFace.Edges();
		
		std::shared_ptr<edgeList> QEdges_ptr;
		auto& QEdges = *QEdges_ptr;
		for (const auto& x : edges)
		{
			Debug_Null_Pointer(x);
			const auto& edge = *x;

			realList Parameters3;
			SplitParameters(edge, theEngine, Parameters3);

			if (Parameters3.empty())
			{
				QEdges.push_back(x);
				continue;
			}

			realList Parameters2;
			CalcParametersOfPlaneCurve(edge, Parameters3, Parameters2);

			auto subEdges = SubdivideEdge(edge, Parameters2, Parameters3);
			for (const auto& sub : subEdges)
				QEdges.push_back(sub);
		}

		Standard_Integer K = 0;
		for (const auto& x : QEdges)
		{
			x->SetIndex(++K);
			x->Par()->SetIndex(K);
		}

		auto face=std::make_shared<Solid_Face>()
	}*/

	static void MatchEdges(const pairedList& FreeEdges, const geoEngine& theEngine, const faceList& theFaces, faceList& Faces)
	{
		Adt_AvlTree<std::shared_ptr<Solid_Face>> merge;
		merge.SetComparableFunction(&Solid_Face::IsLess);

		for (const auto& x : FreeEdges)
		{
			Debug_Null_Pointer(x);
			Debug_Null_Pointer(x->Edge0());
			Debug_Null_Pointer(x->Edge0()->Face().lock());
			merge.InsertIgnoreDup(x->Edge0()->Face().lock());
		}

		faceList surfaces;
		merge.RetrieveTo(surfaces);


	}
}

//void AutLib::Cad3d_SolidTools::MatchEdges
//(
//	const solid_ptr & theSolid,
//	solid_ptr & modified
//)
//{
//}

TopoDS_Shape 
AutLib::Cad3d_SolidTools::RepairWithIGES
(
	const TopoDS_Shape & theShape
)
{
	IGESControl_Controller::Init();

	IGESControl_Writer Writer("MM", 0);
	Writer.AddShape(theShape);
	Writer.ComputeModel();

	Standard_Boolean OK = Writer.Write("~GetSolid_RepairWithIGES.tmp");

	IO_IGES reader;
	reader.SetToFixShape();
	reader.SetVerbose(2);
	reader.ReadFile("~GetSolid_RepairWithIGES.tmp");

	TopoDS_Shape Shape = reader.Shape();

	std::remove("~GetSolid_AutMarine.tmp");

	return Shape;
}