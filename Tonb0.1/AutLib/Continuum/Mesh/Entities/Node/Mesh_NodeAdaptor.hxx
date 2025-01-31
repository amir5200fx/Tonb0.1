#pragma once
#ifndef _Mesh_NodeAdaptor_Header
#define _Mesh_NodeAdaptor_Header

#include <Adt_AvlTree.hxx>
#include <Mesh_EntityAdaptorM.hxx>

namespace AutLib
{

	Mesh_EntityToEntityAdaptor(Node, Edge, EdgeType);
	Mesh_EntityToEntityAdaptor(Node, Facet, FacetType);
	Mesh_EntityToEntityAdaptor(Node, Element, ElementType);

	template<class EdgeType, class ElementType, class FacetType = void>
	class Mesh_NodeAdaptor
		: public Mesh_NodeToEdgeAdaptor<EdgeType>
		, public Mesh_NodeToFacetAdaptor<FacetType>
		, public Mesh_NodeToElementAdaptor<ElementType>
	{

	public:

		typedef Mesh_NodeToEdgeAdaptor<EdgeType> edgeAdaptor;
		typedef Mesh_NodeToFacetAdaptor<FacetType> facetAdaptor;
		typedef Mesh_NodeToElementAdaptor<ElementType> elementAdaptor;

	private:

		/*Private Data*/

	public:

		Mesh_NodeAdaptor()
		{}
	};

	template<class EdgeType, class ElementType>
	class Mesh_NodeAdaptor<EdgeType, ElementType, void>
		: public Mesh_NodeToEdgeAdaptor<EdgeType>
		, public Mesh_NodeToElementAdaptor<ElementType>
	{

	public:

		typedef Mesh_NodeToEdgeAdaptor<EdgeType> edgeAdaptor;
		typedef Mesh_NodeToElementAdaptor<ElementType> elementAdaptor;

	private:

		/*Private Data*/

	public:

		Mesh_NodeAdaptor()
		{}
	};
}

#endif // !_Mesh_NodeAdaptor_Header
