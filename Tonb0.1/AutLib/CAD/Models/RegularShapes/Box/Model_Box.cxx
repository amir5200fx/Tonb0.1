#include <Model_Box.hxx>

#include <BRepPrimAPI_MakeBox.hxx>

void AutLib::Model_Box::Make()
{
	auto P1 = theParameters_.theP0;
	
	auto dx = theParameters_.theDx;
	auto dy = theParameters_.theDy;
	auto dz = theParameters_.theDz;

	Pnt3d P2(P1.X() + dx, P1.Y() + dy, P1.Z() + dz);

	BRepPrimAPI_MakeBox Shape(P1, P2);

	Entity() = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	IsDone() = Standard_True;
}