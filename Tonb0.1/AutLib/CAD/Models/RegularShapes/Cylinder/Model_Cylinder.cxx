#include <Model_Cylinder.hxx>

#include <BRepPrimAPI_MakeCylinder.hxx>

void AutLib::Model_Cylinder::Make()
{
	BRepPrimAPI_MakeCylinder Shape(theParameters_.theRadius, theParameters_.theHeight);

	Entity() = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	IsDone() = Standard_True;
}