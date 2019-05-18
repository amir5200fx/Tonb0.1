#include <Model_Torus.hxx>

#include <BRepPrimAPI_MakeTorus.hxx>

void AutLib::Model_Torus::Make()
{
	BRepPrimAPI_MakeTorus Shape(theParameters_.theR1, theParameters_.theR2);

	Entity() = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	IsDone() = Standard_True;
}