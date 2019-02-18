#pragma once
#ifndef _Mesh_TriElement_Header
#define _Mesh_TriElement_Header

#include <Mesh_Facet.hxx>
#include <error.hxx>
#include <OSstream.hxx>

namespace AutLib
{

	template<class EdgeType, class ElementAdaptor, class FacetType = void>
	class Mesh_TriElement {};

	template<class EdgeType, class ElementAdaptor>
	class Mesh_TriElement<EdgeType, ElementAdaptor, void>
		: public Mesh_Facet<EdgeType, ElementAdaptor, 3>
	{


		typedef Mesh_Facet<EdgeType, ElementAdaptor, 3> base;
		typedef typename EdgeType::nodeType nodeType;

		typedef pHandle(nodeType) nodeType_ptr;
		typedef pHandle(EdgeType) edgeType_ptr;

		/*Private Data*/

	public:

		typedef nodeType nodeType;
		typedef EdgeType edgeType;

		enum
		{
			dim = 2
		};

		Mesh_TriElement()
		{}

		Mesh_TriElement
		(
			const Standard_Integer theIndex
		)
			: base(theIndex)
		{}

		Standard_Integer OppositeVertexIndex
		(
			const Mesh_TriElement& theElement
		) const
		{
			Standard_Integer Index = -1;
			Standard_Address Adress =
				(Standard_Address)&theElement;

			forThose(Iter, 0, 2)
			{
				if (base::Element(Iter) IS_EQUAL Adress)
					return Iter;
			}

			if (Index < 0)
			{
				FatalErrorIn(FunctionSIG)
					<< "NOT FIND opposite vertex"
					<< abort(FatalError);
			}
			return Index;  // Prevent compiler warning
		}

		Standard_Integer OppositeVertexIndex
		(
			const EdgeType& theEdge
		) const
		{
			Standard_Integer Index = -1;
			Standard_Address Adress =
				(Standard_Address)&theEdge;

			forThose(Iter, 0, 2)
			{
				if (base::Edge(Iter) IS_EQUAL Adress)
					return Iter;
			}

			if (Index < 0)
			{
				FatalErrorIn(FunctionSIG)
					<< "NOT FIND opposite vertex"
					<< abort(FatalError);
			}
			return Index;  // Prevent compiler warning
		}

		const nodeType_ptr& OppositeVertex
		(
			const Mesh_TriElement& theElement
		) const
		{
			Standard_Address Adress =
				(Standard_Address)&theElement;

			forThose(Iter, 0, 2)
			{
				if (base::Element(Iter) IS_EQUAL Adress)
					return base::Node(Iter);
			}
			return nodeType::null;
		}

		const nodeType_ptr& OppositeVertex
		(
			const EdgeType& theEdge
		) const
		{
			Standard_Address Adress =
				(Standard_Address)&theEdge;

			forThose(Iter, 0, 2)
			{
				if (base::Edge(Iter) IS_EQUAL Adress)
					return base::Node(Iter);
			}

			return nodeType::null;
		}
	};
}

#endif // !_Mesh_TriElement_Header
