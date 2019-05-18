#include <Solid_Vertex.hxx>

#include <Solid_Ring.hxx>
#include <Solid_Face.hxx>

void AutLib::Solid_Vertex::SetComparableFunction()
{
	theEdges_.SetComparableFunction(&Solid_Edge::IsLess);
	theFaces_.SetComparableFunction(&Solid_Face::IsLess);
}

Standard_Integer AutLib::Solid_Vertex::NbRings() const
{
	Standard_Integer K = 0;
	edgeList edges;
	RetrieveEdgesTo(edges);

	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x.lock());
		if (std::dynamic_pointer_cast<Solid_Ring>(x.lock()))
		{
			K++;
		}
	}
	return K;
}