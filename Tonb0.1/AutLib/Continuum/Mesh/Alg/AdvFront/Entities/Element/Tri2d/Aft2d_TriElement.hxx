#pragma once
#ifndef _Aft2d_TriElement_Header
#define _Aft2d_TriElement_Header

#include <Mesh_TriElement.hxx>
#include <Aft2d_Node.hxx>
#include <Aft2d_Edge.hxx>
#include <Aft2d_TriElementAdaptor.hxx>

namespace AutLib
{

	typedef Mesh_TriElement<Aft2d_Edge, Aft2d_TriElementAdaptor> Aft2d_TriElementBase;

	class Aft2d_TriElement
		: public Aft2d_TriElementBase
	{

		/*Private Data*/

	public:

		typedef Aft2d_TriElementBase base;
		typedef pHandle(Aft2d_Node) node_ptr;
		typedef pHandle(Aft2d_Edge) edge_ptr;

		typedef Aft2d_Edge front_type;

		enum
		{
			dim = 2,   // Dimensionality of edge2d
			rank = 2,   // Rank of TriElement2d is 2
			nbNodes = 3,
			nbEdges = 3,
			nbFronts = 3
		};

		Aft2d_TriElement()
		{}

		Aft2d_TriElement
		(
			const Standard_Integer theIndex
		)
			: base(theIndex)
		{}

		Aft2d_TriElement
		(
			const Standard_Integer theIndex,
			const node_ptr& theNode0,
			const node_ptr& theNode1,
			const node_ptr& theNode2
		)
			: base(theIndex)
		{
			Node(0) = theNode0;
			Node(1) = theNode1;
			Node(2) = theNode2;
		}

		/*edge_ptr FrontEntity
		(
			const Standard_Integer theIndex
		) const
		{
			return base::Edge(theIndex);
		}*/
	};
}

#endif // !_Aft2d_TriElement_Header
