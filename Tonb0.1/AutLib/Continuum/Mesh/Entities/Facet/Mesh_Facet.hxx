#pragma once
#ifndef _Mesh_Facet_Header
#define _Mesh_Facet_Header

#include <Global_Macros.hxx>
#include <handle.hxx>
#include <Mesh_Entity.hxx>

namespace AutLib
{

	template<class EdgeType, class FacetAdaptor, int NbCmpts>
	class Mesh_Facet
	{};

	template<class EdgeType, class FacetAdaptor>
	class Mesh_Facet<EdgeType, FacetAdaptor, 3>
		: public Mesh_Entity
		, public FacetAdaptor
	{

	public:

		typedef typename EdgeType::nodeType nodeType;
		typedef EdgeType edgeType;

		static const int nbCmpts = 3;

	private:

		typedef pHandle(nodeType) nodeType_ptr;
		typedef pHandle(EdgeType) edgeType_ptr;

	private:

		/*Private Data*/

		nodeType_ptr theNodes_[3];
		edgeType_ptr theEdges_[3];

		DisallowBitWiseCopy(Mesh_Facet);

	public:
	

		Mesh_Facet()
		{}

		Mesh_Facet
		(
			const Standard_Integer theIndex
		)
			: Mesh_Entity(theIndex)
		{}

		const nodeType_ptr& Node(const Standard_Integer theIndex) const
		{
			return theNodes_[theIndex];
		}

		nodeType_ptr& Node(const Standard_Integer theIndex)
		{
			return theNodes_[theIndex];
		}

		const edgeType_ptr& Edge(const Standard_Integer theIndex) const
		{
			return theEdges_[theIndex];
		}

		edgeType_ptr& Edge(const Standard_Integer theIndex)
		{
			return theEdges_[theIndex];
		}

		void SetNode
		(
			const Standard_Integer theIndex,
			const nodeType_ptr& theNode
		)
		{
			theNodes_[theIndex] = theNode;
		}

		void SetEdge
		(
			const Standard_Integer theIndex,
			const edgeType_ptr& theEdge
		)
		{
			theEdges_[theIndex] = theEdge;
		}
	};
}

#endif // !_Mesh_Facet_Header
