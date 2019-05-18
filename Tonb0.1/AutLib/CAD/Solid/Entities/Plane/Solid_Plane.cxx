#include <Solid_Plane.hxx>

#include <Solid_Face.hxx>
#include <Solid_Wire.hxx>
#include <Solid_Edge.hxx>
#include <Solid_Curve.hxx>
#include <Solid_parCurve.hxx>
#include <Solid_parEdge.hxx>
#include <Solid_parWire.hxx>

namespace AutLib
{

	static std::shared_ptr<Solid_parWire> GetWire(const Solid_Wire& theWire)
	{
		auto edges_ptr =
			std::make_shared<std::vector<std::shared_ptr<Solid_parEdge>>>();
		auto& edges = *edges_ptr;
		edges.reserve(theWire.NbEdges());

		Standard_Integer K = 0;
		for (const auto& x : *theWire.Edges())
		{
			Debug_Null_Pointer(x);

			const auto& xCurve = x->Par();
			Debug_Null_Pointer(xCurve);

			auto pCurve =
				std::make_shared<Solid_parCurve>
				(
					xCurve->FirstParameter(),
					xCurve->LastParameter(),
					xCurve->Curve()
					);

			auto pEdge =
				std::make_shared<Solid_parEdge>(++K, pCurve);

			edges.push_back(pEdge);
		}

		auto wire =
			std::make_shared<Solid_parWire>(edges_ptr);

		return std::move(wire);
	}
}

void AutLib::Solid_Plane::RetrieveWiresTo(wireList & theWires) const
{
	theWires.push_back(theOutter_);
	if (theInner_)
	{
		for (const auto& x : *theInner_)
		{
			theWires.push_back(x);
		}
	}
}

std::shared_ptr<AutLib::Solid_Plane> 
AutLib::Solid_Plane::MakePlane
(
	const Solid_Face & theFace
)
{
	if (NOT theFace.OuterWire())
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid Face : has no outer wire" << endl
			<< abort(FatalError);
	}

	const auto& Outer = *theFace.OuterWire();
	const auto& Inners = *theFace.InnerWires();

	auto outer_wire = 
		GetWire(Outer);

	std::shared_ptr<std::vector<std::shared_ptr<Solid_parWire>>> inner_wires;
	if (theFace.InnerWires())
	{
		inner_wires = std::make_shared<std::vector<std::shared_ptr<Solid_parWire>>>();
		inner_wires->reserve(Inners.size());

		for (const auto& x : Inners)
		{
			Debug_Null_Pointer(x);

			auto wire = GetWire(*x);
			inner_wires->push_back(wire);
		}
	}

	auto plane = 
		std::make_shared<Solid_Plane>(outer_wire, inner_wires);
	return std::move(plane);
}