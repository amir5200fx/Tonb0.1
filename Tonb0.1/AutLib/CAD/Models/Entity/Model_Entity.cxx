#include <Model_Entity.hxx>

#include <dictionary.hxx>
#include <TecPlot_Opencascade.hxx>
#include <fileName.hxx>
#include <OFstream.hxx>
#include <TopoDS.hxx>
#include <Entity3d_Box.hxx>
#include <Bnd_Box.hxx>
#include <BRepBndLib.hxx>
#include <BRep_Tool.hxx>
#include <BRepMesh_FastDiscret.hxx>
#include <TopExp_Explorer.hxx>
#include <TopLoc_Location.hxx>
#include <IGESControl_Controller.hxx>
#include <IGESControl_Writer.hxx>
#include <Poly_Triangulation.hxx>

#include <BRepAlgoAPI_Section.hxx>

namespace AutLib
{
	const Standard_Real Model_EntityDiscrete::DEFAULT_DEFLECTION((Standard_Real)0.01);
	const Standard_Real Model_EntityDiscrete::DEFAULT_ANGLE((Standard_Real)0.1);
}

AutLib::Model_EntityIO::Model_EntityIO()
	: theDict_(dictionary::null)
	, theFileName_("myModel")
	, theFormat_(Io::EntityIO_Format_TecPlot)
{}

TopoDS_Shape AutLib::Model_Entity::Section(const gp_Pln & thePlane) const
{
	if (Entity().IsNull())
	{
		FatalErrorIn(" TopoDS_Shape AutLib::Model_Entity::Section(const gp_Pln & thePlane) const")
			<< " null model"
			<< abort(FatalError);
	}

	BRepAlgoAPI_Section Section(Entity(), thePlane);
	return Section.Shape();
}

void AutLib::Model_Entity::Discrete()
{
	if (NOT IsDone())
		return;

	if (Entity().IsNull())
	{
		FatalErrorIn("void AutLib::Model_Entity::Discrete()")
			<< " No entity has been found!"
			<< abort(FatalError);
	}

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = Deflection();
	Params.Angle = Angle();

	Bnd_Box box;
	BRepBndLib::Add(Entity(), box);
	BRepMesh_FastDiscret Mesh(box, Params);

	if (!Box())
	{
		Box() = std::make_shared<Entity3d_Box>(box.CornerMin(), box.CornerMax());
	}

	Mesh.Perform(Entity());
}

namespace AutLib
{

	static void ExportToPlt
	(
		const TopoDS_Shape& theShape,
		const fileName& name
	)
	{
		OFstream File(name);

		for (TopExp_Explorer Explorer(theShape, TopAbs_FACE); Explorer.More(); Explorer.Next())
		{
			TopLoc_Location Loc;
			Handle(Poly_Triangulation) Triangulation =
				BRep_Tool::Triangulation(TopoDS::Face(Explorer.Current()), Loc);

			if (Triangulation.IsNull()) continue;

			Io::ExportMesh(Triangulation->Nodes(), Triangulation->Triangles(), File);
		}
	}

	static void ExportToIGES
	(
		const word& unit,
		const TopoDS_Shape& theShape,
		const fileName& name
	)
	{
		IGESControl_Controller::Init();

		IGESControl_Writer Writer(unit.c_str(), 0);
		Writer.AddShape(theShape);
		Writer.ComputeModel();

		Standard_Boolean OK = Writer.Write(name.c_str());
	}
}

void AutLib::Model_Entity::ExportToFile() const
{
	fileName name_of_file(FileName());

	switch (IO().FileFromat())
	{
	case Io::EntityIO_Format_TecPlot:
		name_of_file += ".plt";
		break;
	case Io::EntityIO_Format_STEP:
		name_of_file += ".step";
		break;
	case Io::EntityIO_Format_IGES:
		name_of_file += ".iges";
		break;
	}

	switch (IO().FileFromat())
	{
	case Io::EntityIO_Format_TecPlot:
		ExportToPlt(Entity(), name_of_file);
		break;
	case Io::EntityIO_Format_STEP:
		break;
	case Io::EntityIO_Format_IGES:
		ExportToIGES("MM", Entity(), name_of_file);
		break;
	}
}

void AutLib::Model_Entity::CalcBoundingBox()
{
	if (!Box())
	{
		Bnd_Box box;
		BRepBndLib::Add(Entity(), box);

		Box() = std::make_shared<Entity3d_Box>(box.CornerMin(), box.CornerMax());
	}
}

AutLib::Entity3d_Box AutLib::Model_Entity::BoundingBox(const TopoDS_Shape & theShape)
{
	Bnd_Box box;
	BRepBndLib::Add(theShape, box);

	return Entity3d_Box(box.CornerMin(), box.CornerMax());
}