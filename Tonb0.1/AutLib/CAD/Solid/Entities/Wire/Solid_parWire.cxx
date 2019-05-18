#include <Solid_parWire.hxx>

#include <Solid_parEdge.hxx>
#include <Solid_parCurve.hxx>

AutLib::Solid_parWireTolerance::Solid_parWireTolerance()
	: Tolerance(1.0E-3)
{}

void AutLib::Solid_parWire::CheckWire()
{
	if (NOT theEdges_)
	{
		FatalErrorIn("void AutLib::Solid_parWire::CheckWire()")
			<< "Null wire" << endl
			<< abort(FatalError);
	}

	const auto& edges = *theEdges_;
	if (edges.size() IS_EQUAL 1)
	{
		const auto& edge = edges[0];
		if (NOT edge->IsRing())
		{
			FatalErrorIn("void AutLib::Solid_parWire::CheckWire()")
				<< "Invalid Wire: the edge is not a ring" << endl
				<< abort(FatalError);
		}
		return;
	}

	forThose(Index, 1, edges.size() - 1)
	{
		const auto& curve0 = edges[Index - 1]->Curve();
		const auto& curve1 = edges[Index]->Curve();

		if (curve0->Last().Distance(curve1->Start()) > Tolerance)
		{
			FatalErrorIn("void AutLib::Solid_parWire::CheckWire()")
				<< "Invalid Wire" << endl
				<< abort(FatalError);
		}
	}

	const auto& last = edges[edges.size() - 1]->Curve();
	const auto& first = edges[0]->Curve();

	if (last->Last().Distance(first->Start()) > Tolerance)
	{
		FatalErrorIn("void AutLib::Solid_parWire::CheckWire()")
			<< "Invalid Wire: the wire is not closed" << endl
			<< abort(FatalError);
	}
}
