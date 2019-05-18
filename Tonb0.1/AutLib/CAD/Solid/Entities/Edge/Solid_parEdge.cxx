#include <Solid_parEdge.hxx>

#include <Solid_parCurve.hxx>

Standard_Boolean AutLib::Solid_parEdge::IsRing() const
{
	Debug_Null_Pointer(Curve());
	const auto& geom = *Curve();

	const auto P0 = geom.Start();
	const auto P1 = geom.Last();

	return P0.Distance(P1) <= gp::Resolution();
}