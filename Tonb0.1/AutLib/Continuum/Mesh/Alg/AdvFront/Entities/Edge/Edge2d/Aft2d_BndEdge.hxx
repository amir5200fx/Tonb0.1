#pragma once
#ifndef _Aft2d_BndEdge_Header
#define _Aft2d_BndEdge_Header

#include <Aft2d_Edge.hxx>

namespace AutLib
{

	class Aft2d_BndEdge
		: public Aft2d_Edge
	{

		/*Private Data*/

	public:

		typedef Aft2d_Edge base;

		typedef Aft2d_Node node;
		typedef Aft2d_Edge edge;

		typedef pHandle(node) node_ptr;
		typedef pHandle(edge) edge_ptr;

		Aft2d_BndEdge()
		{}

		Aft2d_BndEdge(const Standard_Integer theIndex)
			: base(theIndex)
		{}

		Aft2d_BndEdge
		(
			const Standard_Integer theIndex,
			const node_ptr& theNode0,
			const node_ptr& theNode1
		)
			: base(theIndex, theNode0, theNode1)
		{}

		virtual ~Aft2d_BndEdge()
		{}
	};
}

#endif // !_Aft2d_BndEdge_Header
