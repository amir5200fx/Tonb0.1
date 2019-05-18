#include <Model_Cone.hxx>

#include <BRepPrimAPI_MakeCone.hxx>

void AutLib::Model_Cone::Make()
{
	BRepPrimAPI_MakeCone Shape(theParameters_.theR1, theParameters_.theR2, theParameters_.theHeight);

	Entity() = Shape.Solid().Oriented(TopAbs_Orientation::TopAbs_FORWARD);

	IsDone() = Standard_True;
}