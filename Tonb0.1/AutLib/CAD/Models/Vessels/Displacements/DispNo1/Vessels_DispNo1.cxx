#include <Vessels_DispNo1.hxx>

#include <gp_Pln.hxx>
#include <Geom_BSplineSurface.hxx>
#include <GeomFill_BSplineCurves.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Edge.hxx>
#include <TopExp_Explorer.hxx>
#include <BRep_Tool.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgoAPI_Section.hxx>
#include <TColGeom_Array1OfBSplineCurve.hxx>

const char* const AutLib::DispNo1_BareHull::typeName = "DispNo1_BareHull";
const char* const AutLib::DispNo1_HullPatch::typeName = "DispNo1_HullPatch";

void AutLib::DispNo1_HullPatch::AllocateMemory()
{
	const auto& dimensions = Dimensions();

	auto nbSections = dimensions.NbNetColumns().Value();
	auto nbRows = dimensions.NbNetRows().Value();

	DispNo1_Xparams::AllocateMemory(nbSections);

	DispNo1_Profile::AllocateMemory(nbSections);

	CtrlNet =
		std::make_shared<TColgp_Array2OfPnt>(1, nbSections, 1, nbRows);
}

void AutLib::DispNo1_HullPatch::MakeFace()
{
	Model_Entity::Entity() =
		BRepBuilderAPI_MakeFace(theHull_, 1.0E-6);

	Model_EntitySystem::System() =
		gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0));
}

void AutLib::DispNo1_HullPatch::Perform()
{
	AllocateMemory();

	CalcxXSections();

	CalcxParameters();

	CreateRawSections();

	ApplyParameters();

	SetupControlNet();

	SetupPatch();

	MakeFace();

	IsDone_ = Standard_True;
}

TopoDS_Shape AutLib::DispNo1_HullPatch::GetStation(const Standard_Real theX) const
{
	BRepAlgoAPI_Section Section(Entity(), gp_Pln(gp_Pnt(theX, 0, 0), gp_Dir(1, 0, 0)));
	return Section.Shape();
}

TopoDS_Shape AutLib::DispNo1_HullPatch::GetButtock(const Standard_Real theY) const
{
	BRepAlgoAPI_Section Section(Entity(), gp_Pln(gp_Pnt(0, theY, 0), gp_Dir(0, 1, 0)));
	return Section.Shape();
}

TopoDS_Shape AutLib::DispNo1_HullPatch::GetWater(const Standard_Real theZ) const
{
	BRepAlgoAPI_Section Section(Entity(), gp_Pln(gp_Pnt(0, 0, theZ), gp_Dir(0, 0, 1)));
	return Section.Shape();
}

void AutLib::DispNo1_BareHull::MakeFace()
{
	DispNo1_HullPatch::MakeFace();

	auto Hull = Handle(Geom_BSplineSurface)::DownCast(Patch());

	if (Hull.IsNull())
	{
		FatalErrorIn("void AutLib::Cad_ShipBareHull::MakeFace()")
			<< " No patch has been found"
			<< abort(FatalError);
	}

	Handle(Geom_BSplineSurface) Pair = new Geom_BSplineSurface
	(
		Hull->Poles(),
		Hull->UKnots(),
		Hull->VKnots(),
		Hull->UMultiplicities(),
		Hull->VMultiplicities(),
		Hull->UDegree(),
		Hull->VDegree()
	);
	Pair->Mirror(System());

	TopoDS_Shape PairShape = BRepBuilderAPI_MakeFace(Pair, 1.0E-6);
	PairShape.Reverse();

	Entity() = BRepAlgoAPI_Fuse(Entity(), PairShape);

	TColGeom_Array1OfBSplineCurve Curves(1, 8);
	Standard_Integer K = 0;
	for (TopExp_Explorer Explorer(Entity(), TopAbs_EDGE); Explorer.More(); Explorer.Next())
	{
		TopoDS_Edge Edge = TopoDS::Edge(Explorer.Current());
		TopLoc_Location Loc;
		Standard_Real First, Last;
		Handle(Geom_Curve) Curve = BRep_Tool::Curve(Edge, First, Last);

		Handle(Geom_BSplineCurve) BSplCurve = Handle(Geom_BSplineCurve)::DownCast(Curve);

		if (BSplCurve.IsNull())
		{
			FatalErrorIn(" void AutLib::Cad_ShipBareHull::MakeFace()")
				<< " Null caurve encountered"
				<< abort(FatalError);
		}

		Curves.SetValue(++K, BSplCurve);
	}

	GeomFill_BSplineCurves Transom(Curves.Value(1), Curves.Value(5), GeomFill_CoonsStyle);
	Entity() = BRepAlgoAPI_Fuse(Entity(), BRepBuilderAPI_MakeFace(Transom.Surface(), 1.0E-6));

	GeomFill_BSplineCurves Deck(Curves.Value(3), Curves.Value(7), GeomFill_CoonsStyle);
	Entity() = BRepAlgoAPI_Fuse(Entity(), BRepBuilderAPI_MakeFace(Deck.Surface(), 1.0E-6));
}