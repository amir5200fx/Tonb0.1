#include <Cad3d_SolidTools.hxx>

#include <Solid_Curve.hxx>
#include <Solid_parCurve.hxx>
#include <Solid_Edge.hxx>
#include <Solid_Ring.hxx>
#include <Solid_Wire.hxx>
#include <Solid_Face.hxx>

#include <Geom2d_Curve.hxx>
#include <Geom_Curve.hxx>
#include <Geom_Surface.hxx>
#include <Geom2dAPI_ProjectPointOnCurve.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shape.hxx>
#include <TopExp_Explorer.hxx>
#include <BRepTools_WireExplorer.hxx>
#include <BRep_Tool.hxx>
#include <BRepTools.hxx>
#include <BRepLib.hxx>
#include <ShapeFix_Wire.hxx>
#include <ShapeFix_ShapeTolerance.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <ShapeAnalysis_Wire.hxx>

namespace AutLib
{

	/*struct MergingTolerance
	{

		Standard_Real theMinTol;
		Standard_Real theMaxTol;

		Standard_Integer theNbLevels;

		MergingTolerance()
			: theMinTol(1.0E-8)
			, theMaxTol(1.0E-2)
			, theNbLevels(5)
		{}
	};*/


	/*static Pnt2d LowerDistanceFromCurveEnds
	(
		const Pnt2d& theP0,
		const Pnt2d& theP1,
		const Solid_parCurve& theCurve
	)
	{
		auto P0 = theCurve.Start();
		auto P1 = theCurve.Last();

		auto D0 = 
			MIN(SquareDistance(theP0, P0), SquareDistance(theP0, P1));
		auto D1 = 
			MIN(SquareDistance(theP1, P0), SquareDistance(theP1, P1));

		if (D0 < D1) return theP0;
		else return theP1;
	}*/

	/*static Standard_Boolean CalcMinDistance
	(
		const Pnt2d& theCoord,
		const Solid_parCurve& theCurve, 
		Standard_Real& param, 
		Standard_Real& minDist
	)
	{
		Geom2dAPI_ProjectPointOnCurve Proj
		(
			theCoord, 
			theCurve.Curve(),
			theCurve.FirstParameter(),
			theCurve.LastParameter()
		);

		if (NOT Proj.NbPoints()) return Standard_True;
		param = Proj.LowerDistanceParameter();
		minDist = Proj.LowerDistance();
		return Standard_False;
	}*/

	/*static Standard_Boolean CheckConsecutive
	(
		const Solid_parEdge& theEdge0,
		const Solid_parEdge& theEdge1,
		const MergingTolerance& theInfo
	)
	{
		const auto P0 = theEdge0.Geometry()->Last();
		const auto P1 = theEdge1.Geometry()->Start();

		const auto tol0_log = log10(theInfo.theMinTol);
		const auto tol1_log = log10(theInfo.theMaxTol);

		auto dt_log = (tol1_log - tol0_log) / theInfo.theNbLevels;

		forThose(i, 0, theInfo.theNbLevels)
		{
			const auto tol = pow(i * dt_log + tol0_log, 10.0);

			if()
		}
	}*/

	/*static void ModifyEndings(const std::vector<std::shared_ptr<Solid_Edge>>& Edges, const MergingTolerance& theInfo)
	{
		if (Edges.size() < 2) return;

		forThose(Index, 0, Edges.size() - 1)
		{
			Debug_Null_Pointer(Edges[Index]);
			Debug_Null_Pointer(Edges[Index + 1]);

			const auto& edge0 = *Edges[Index];
			const auto& edge1 = *Edges[Index + 1];


		}
	}*/

	void CheckWire(const TopoDS_Wire &wire, const TopoDS_Face &face, const Standard_Real precision)
	{
		ShapeAnalysis_Wire analysis(wire, face, precision);

		if (NOT analysis.IsLoaded())
		{
			FatalErrorIn("CheckWire(const TopoDS_Wire &wire, const TopoDS_Face &face, const Standard_Real precision)")
				<< "the wire is not loaded" << endl
				<< abort(FatalError);
		}

		if (NOT analysis.IsReady())
		{
			FatalErrorIn("CheckWire(const TopoDS_Wire &wire, const TopoDS_Face &face, const Standard_Real precision)")
				<< "the face is not loaded" << endl
				<< abort(FatalError);
		}
		cout << "perform = " << analysis.Perform() << std::endl;
		/*if (NOT analysis.Perform())
		{
			return;
		}*/

		cout << "something goes wrong!" << std::endl;
	}

	void CheckEdge
	(
		const Handle(Geom2d_Curve)& thePCurve,
		const Standard_Real u0,
		const Standard_Real u1,
		const Handle(Geom_Curve)& theCurve, 
		const Standard_Real U0, 
		const Standard_Real U1, 
		const Handle(Geom_Surface)& theSurface
	)
	{
		const auto p0 = thePCurve->Value(u0);
		const auto p1 = thePCurve->Value(u1);

		const auto s0 = theSurface->Value(p0.X(), p0.Y());
		const auto s1 = theSurface->Value(p1.X(), p1.Y());

		const auto S0 = theCurve->Value(U0);
		const auto S1 = theCurve->Value(U1);

		if (s0.Distance(S0) >= 1.0E-6)
		{
			//if (s0.Distance(S1) <= 1.0E-6) return;
			//cout << "dis = " << s0.Distance(S0) << std::endl;
			FatalErrorIn("void CheckEdge()")
				<< "It's supposed that the edge has SameRange flag" << endl
				<< "dis = " << s0.Distance(S0) << endl
				<< abort(FatalError);
		}

		if (s1.Distance(S1) >= 1.0E-6)
		{
			//if (s1.Distance(S0) <= 1.0E-6) return;
			FatalErrorIn("void CheckEdge()")
				<< "It's supposed that the edge has SameRange flag" << endl
				<< "dis = " << s1.Distance(S1) << endl
				<< abort(FatalError);
		}
	}

	std::shared_ptr<Solid_Edge> GetNewEdge
	(
		Standard_Integer& K,
		const TopoDS_Edge edge,
		const TopoDS_Face theFace
	)
	{
		Standard_Real u0, u1, U0, U1;
		TopLoc_Location pLoc, eLoc;
		auto patch = BRep_Tool::Surface(theFace, pLoc);

		auto pCurve = BRep_Tool::CurveOnSurface(edge, patch, pLoc, u0, u1);
		auto Curve = BRep_Tool::Curve(edge, eLoc, U0, U1);

		if (NOT BRep_Tool::SameRange(edge))
		{
			BRepLib::SameRange(edge);
		}

		if (NOT BRep_Tool::SameParameter(edge))
		{
			FatalErrorIn("AutLib::Cad3d_SolidTools::face_ptr AutLib::Cad3d_SolidTools::GetSurface(const TopoDS_Face & theFace)")
				<< "It's supposed that the edge has SameParameter flag" << endl
				<< abort(FatalError);
		}

		if (NOT BRep_Tool::SameRange(edge))
		{
			FatalErrorIn("AutLib::Cad3d_SolidTools::face_ptr AutLib::Cad3d_SolidTools::GetSurface(const TopoDS_Face & theFace)")
				<< "It's supposed that the edge has SameRange flag" << endl
				<< abort(FatalError);
		}

		//CheckEdge(pCurve, u0, u1, Curve, U0, U1, BRep_Tool::Surface(theFace));

		if (edge.Orientation() IS_EQUAL TopAbs_REVERSED)
		{
			auto temp = u1;
			u1 = pCurve->ReversedParameter(u0);
			u0 = pCurve->ReversedParameter(temp);
			pCurve->Reverse();
		}	

		auto curveOnPlane = std::make_shared<Solid_parCurve>(u0, u1, pCurve);

		std::shared_ptr<Solid_Edge> newEdge;

		++K;

		if (Curve)
		{
			auto curveOnSurface = std::make_shared<Solid_Curve>(U0, U1, Curve);
			if (Distance(Curve->Value(U0), Curve->Value(U1)) <= 1.0E-6)
			{
				newEdge = std::make_shared<Solid_Ring>(K, curveOnSurface);
			}
			else
			{
				newEdge = std::make_shared<Solid_Edge>(K, curveOnSurface);
			}
		}
		else
		{
			newEdge = std::make_shared<Solid_Edge>(K, nullptr);
		}

		curveOnPlane->SetIndex(K);
		newEdge->SetPar(curveOnPlane);
		newEdge->SetTEdge(edge);
		//newEdge->SetPrecision(BRep_Tool::Tolerance(edge));

		return std::move(newEdge);
	}
}

AutLib::Cad3d_SolidTools::face_ptr 
AutLib::Cad3d_SolidTools::GetSurface
(
	const TopoDS_Face & theFace
)
{
	const auto forwardFace = TopoDS::Face(theFace.Oriented(TopAbs_FORWARD));

	auto Outter_edges_ptr = std::make_shared<std::vector<std::shared_ptr<Solid_Edge>>>();
	auto& Outter_edges = *Outter_edges_ptr;

	const Standard_Real Tol = 1.0E-4;
	Standard_Integer K = 0;
	Standard_Integer wireIndex = 0;

	const auto outer_wire = BRepTools::OuterWire(forwardFace);

	if (outer_wire.IsNull())
	{
		FatalErrorIn("AutLib::Cad3d_SolidTools::face_ptr AutLib::Cad3d_SolidTools::GetSurface(const TopoDS_Face & theFace)")
			<< "Null outer wire" << endl
			<< abort(FatalError);
	}

	//CheckWire(outer_wire, theFace, 1.0e-3);

	/*ShapeFix_ShapeTolerance FTol;
	BRepBuilderAPI_MakeWire aMakeWire;

	Handle(ShapeFix_Wire) sfw = new ShapeFix_Wire;
	sfw->Load(outer_wire);
	sfw->Perform();

	sfw->FixReorder();
	sfw->SetMaxTolerance(Tol);

	sfw->ClosedWireMode() = Standard_True;
	sfw->FixConnected(1.0E-3);
	sfw->FixClosed(1.0E-3);

	forThose(Index, 1, sfw->WireData()->NbEdges())
	{
		auto Edge = sfw->WireData()->Edge(Index);
		FTol.SetTolerance(Edge, Tol, TopAbs_VERTEX);

		aMakeWire.Add(Edge);
	}

	auto fixed_outer_wire = aMakeWire.Wire();*/

	ShapeFix_Wire SFWF(outer_wire, forwardFace, Tol);

	SFWF.SetPrecision(1.0E-3);
	SFWF.SetMaxTolerance(1.0E-2);
	SFWF.SetMinTolerance(1.0E-6);

	SFWF.FixReorder();
	SFWF.ClosedWireMode() = Standard_True;
	SFWF.FixClosed();
	SFWF.FixConnected();

	SFWF.Perform();

	auto fixed_outer_wire = SFWF.Wire();

	for (
		BRepTools_WireExplorer anEdgeExp(fixed_outer_wire);
		anEdgeExp.More();
		anEdgeExp.Next()
		)
	{
		auto edge = TopoDS::Edge(anEdgeExp.Current());
		auto new_edge = GetNewEdge(K, edge, forwardFace);

		Outter_edges.push_back(new_edge);
	}

	auto outerWire = std::make_shared<Solid_Wire>(++wireIndex, Outter_edges_ptr);
	std::shared_ptr<std::vector<std::shared_ptr<Solid_Wire>>> Qwire;
	for (
		TopExp_Explorer aWireExp(forwardFace, TopAbs_WIRE);
		aWireExp.More();
		aWireExp.Next()
		)
	{
		auto wire = TopoDS::Wire(aWireExp.Current());

		if (wire.IsNull()) continue;
		if (wire IS_EQUAL outer_wire) continue;
		// has inner wire

		auto Inner_edges_ptr = std::make_shared<std::vector<std::shared_ptr<Solid_Edge>>>();
		auto& Inner_edges = *Inner_edges_ptr;

		ShapeFix_Wire SFWF(wire, forwardFace, Tol);

		SFWF.SetPrecision(1.0E-3);
		SFWF.SetMaxTolerance(1.0E-2);
		SFWF.SetMinTolerance(1.0E-6);

		SFWF.FixReorder();
		SFWF.ClosedWireMode() = Standard_True;
		SFWF.FixClosed();
		SFWF.FixConnected();

		SFWF.Perform();
		wire = SFWF.WireAPIMake();
	
		for (
			BRepTools_WireExplorer anEdgeExp(wire);
			anEdgeExp.More(); 
			anEdgeExp.Next()
			)
		{
			auto edge = TopoDS::Edge(anEdgeExp.Current());		

			Inner_edges.push_back(GetNewEdge(K, edge, forwardFace));
		}

		if (Inner_edges.empty())
		{
			FatalErrorIn("AutLib::Cad3d_SolidTools::face_ptr AutLib::Cad3d_SolidTools::GetSurface(const TopoDS_Face & theFace)")
				<< "Empty wire" << endl
				<< abort(FatalError);
		}

		auto innerWire = std::make_shared<Solid_Wire>(++wireIndex, Inner_edges_ptr);

		if (NOT Qwire) Qwire = std::make_shared<std::vector<std::shared_ptr<Solid_Wire>>>();
		Qwire->push_back(innerWire);
	}

	TopLoc_Location Location;
	auto geometry = BRep_Tool::Surface(forwardFace, Location);

	auto face = 
		std::make_shared<Solid_Face>(geometry, outerWire, Qwire);

	face->SetTFace(forwardFace);
	face->CalcBoundingBox();

	const auto& edgeList = face->Edges();
	for (auto& x : edgeList)
		x->SetFace(face);

	return std::move(face);
}

AutLib::Cad3d_SolidTools::faceList 
AutLib::Cad3d_SolidTools::GetSurfaces
(
	const TopoDS_Shape & theShape
)
{
	Standard_Integer K = 0;
	faceList list;
	for (
		TopExp_Explorer aFaceExp(theShape.Oriented(TopAbs_FORWARD), TopAbs_FACE);
		aFaceExp.More();
		aFaceExp.Next()
		)
	{
		auto raw = TopoDS::Face(aFaceExp.Current());

		if (raw.IsNull())
		{
			continue;
		}

		auto face = GetSurface(raw);

		if (raw.Orientation() IS_EQUAL TopAbs_REVERSED)
		{
			face->SetOrientation(Face_Orientation_INWARD);
		}
		else
		{
			face->SetOrientation(Face_Orientation_OUTWARD);
		}

		face->SetIndex(++K);
		list.push_back(face);
	}

	return std::move(list);
}