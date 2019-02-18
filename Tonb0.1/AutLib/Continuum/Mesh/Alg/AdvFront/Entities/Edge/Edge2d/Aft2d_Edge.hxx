#pragma once
#ifndef _Aft2d_Edge_Header
#define _Aft2d_Edge_Header

#include <Mesh_Edge.hxx>
#include <Aft2d_Node.hxx>
#include <Aft2d_EdgeAdaptor.hxx>
#include <LocalFrontIdentifiers_FrontEntity.hxx>

namespace AutLib
{

	// Forward Declarations
	class Aft2d_TriElement;
	class Aft2d_BndEdge;

	class Aft2d_Edge
		: public Mesh_Edge<Aft2d_Node, Aft2d_EdgeAdaptor>
		, public LocalFrontIdentifiers_FrontEntity<Aft2d_Node::ptType>
	{

		/*Private Data*/

	public:

		typedef Mesh_Edge<Aft2d_Node, Aft2d_EdgeAdaptor> base;
		typedef LocalFrontIdentifiers_FrontEntity<Aft2d_Node::ptType> front;
		typedef Aft2d_Node node;
		typedef Aft2d_Edge edge;
		typedef Aft2d_BndEdge bndEdge;

		typedef pHandle(node) node_ptr;
		typedef pHandle(edge) edge_ptr;

		enum
		{
			dim = 2,   // Dimensionality of edge2d
			rank = 1,  // Rank of edge2d is 1
			nbNodes = 2
		};


		Aft2d_Edge()
		{}

		Aft2d_Edge
		(
			const Standard_Integer theIndex
		)
			: base(theIndex)
		{}

		Aft2d_Edge
		(
			const Standard_Integer theIndex,
			const node_ptr& theNode0,
			const node_ptr& theNode1
		)
			: base(theIndex, theNode0, theNode1)
		{}

		virtual ~Aft2d_Edge()
		{}

		Standard_Boolean IsOnFront() const
		{
			return Node0()->IsOnFrontEdges(this);
		}

		Standard_Real CalcDistance
		(
			const Pnt2d& theCoord
		) const;

		Standard_Real CalcSquareDistance
		(
			const Pnt2d& theCoord
		) const;

		Standard_Real Oriented(const Pnt2d& theCoord) const;

		Pnt2d CalcOptimumCoord(const Standard_Real theSize) const
		{
			Pnt2d n = (Node1()->Coord() - Centre()).UnitLength();
			n.Rotate90ccw();

			return Centre() + theSize * n;
		}

		static Standard_Boolean IsLess
		(
			const edge_ptr& theEdge0,
			const edge_ptr& theEdge1
		)
		{
			Debug_Null_Pointer(theEdge0);
			Debug_Null_Pointer(theEdge1);
			return theEdge0->Index() < theEdge1->Index();
		}

		static Standard_Boolean IsLessRaw
		(
			const edge* const &theEdge0,
			const edge* const &theEdge1
		)
		{
			Debug_Null_Pointer(theEdge0);
			Debug_Null_Pointer(theEdge1);
			return theEdge0->Index() < theEdge1->Index();
		}
	};
}

#endif // !_Aft2d_Edge_Header
