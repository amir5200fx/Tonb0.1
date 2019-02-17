#pragma once
#ifndef _Aft_Node_Header
#define _Aft_Node_Header

#include <Mesh_Node.hxx>
#include <LocalFrontIdentifiers_Node.hxx>

namespace AutLib
{

	// Forward Declarations
	class Aft2d_Node;
	class Aft3d_Node;

	class Aft2d_Edge;
	class Aft2d_TriElement;

	template<class Point, class NodeAdaptor>
	class Aft_Node
		: public Mesh_Node<Point, NodeAdaptor>
		, public LocalFrontIdentifiers_Node
	{

		typedef Mesh_Node<Point, NodeAdaptor> node;
		typedef LocalFrontIdentifiers_Node front;

		/*Private Data*/

	public:

		typedef Point ptType;

		Aft_Node()
		{}

		Aft_Node
		(
			const Standard_Integer theIndex
		)
			: node(theIndex)
		{}

		Aft_Node
		(
			const Standard_Integer theIndex,
			const Point& theCoord
		)
			: node(theIndex, theCoord)
		{}
	};
}

#endif // !_Aft_Node_Header
