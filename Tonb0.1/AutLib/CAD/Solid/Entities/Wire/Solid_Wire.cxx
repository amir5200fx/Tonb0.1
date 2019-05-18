#include <Solid_Wire.hxx>

#include <Solid_parCurve.hxx>
#include <Solid_Ring.hxx>
#include <Entity2d_Box.hxx>

void AutLib::Solid_Wire::CheckWire()
{
	if (!theEdges_)
	{
		FatalErrorIn("void AutLib::Solid_Wire::CheckWire()")
			<< "Null edge list encountered!" << endl
			<< abort(FatalError);
	}

	const auto& edges = *theEdges_;
	if (!edges.size())
	{
		FatalErrorIn("void AutLib::Solid_Wire::CheckWire()")
			<< "empty edge list encountered!" << endl
			<< abort(FatalError);
	}

	if (edges.size() == 1)
	{
		if (!edges[0]->IsRing())
		{
			FatalErrorIn("void AutLib::Solid_Wire::CheckWire()")
				<< "the edge must be a ring!" << endl
				<< abort(FatalError);
		}
	}
	else
	{
		for (const auto& x : edges)
		{
			if (!x)
			{
				FatalErrorIn("void AutLib::Solid_Wire::CheckWire()")
					<< "Null edge encountered!" << endl
					<< abort(FatalError);
			}

			/*if (x->IsRing())
			{
				FatalErrorIn("void AutLib::Solid_Wire::CheckWire()")
					<< "Invalid wire: there is atleast one ring in the wire" << endl
					<< abort(FatalError);
			}*/
		}

		auto x0 = edges[0];
		auto x = x0;

		for (int k = 1; k < edges.size(); k++)
		{
			x = edges[k];

			if (x->Start() != x0->End())
			{
				FatalErrorIn("void AutLib::Solid_Wire::CheckWire()")
					<< "Invalid wire: the first vertex of the current edge " << endl
					<< " doesnot has coincide with last vertex of the prior one"
					<< abort(FatalError);
			}

			x0 = x;
		}

		if (edges[0]->Start() != edges[edges.size() - 1]->End())
		{
			FatalErrorIn("void AutLib::Solid_Wire::CheckWire()")
				<< "Invalid wire: not closed " << endl
				<< abort(FatalError);
		}
	}
}

AutLib::Entity2d_Box 
AutLib::Solid_Wire::CalcParametricBoundingBox() const
{
	Debug_Null_Pointer(theEdges_);

	const auto& edges = *theEdges_;

	if (edges.empty())
	{
		FatalErrorIn("Entity2d_Box CalcParametricBoundingBox() const")
			<< "the edge list is empty" << endl
			<< abort(FatalError);
	}

	auto box = edges[0]->Par()->BoundingBox();
	forThose(Index, 1, edges.size() - 1)
	{
		box = Entity2d_Box::Union(edges[Index]->Par()->BoundingBox(), box);
	}
	return std::move(box);
}

void AutLib::Solid_Wire::Reverse()
{
	Debug_Null_Pointer(theEdges_);

	const auto& edges = *theEdges_;
	for (auto& x : edges)
	{
		x->Reverse();
	}
}

void AutLib::Solid_Wire::RetrieveVerticesTo(vertexList & theVertices) const
{
	theVertices.reserve(NbEdges());

	Debug_Null_Pointer(theEdges_);
	const auto& edges = *theEdges_;
	for (auto& x : edges)
	{
		theVertices.push_back(x->Start());
	}
}