#include <Model_Sphere.hxx>

#include <BRepPrimAPI_MakeSphere.hxx>

void AutLib::Model_Sphere::Make()
{
	BRepPrimAPI_MakeSphere Shape(theParameters_.theCentre, theParameters_.theRadius);

	Entity() = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	IsDone() = Standard_True;
}