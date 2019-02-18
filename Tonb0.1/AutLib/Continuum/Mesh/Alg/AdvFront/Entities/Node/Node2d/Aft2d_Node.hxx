#pragma once
#ifndef _Aft2d_Node_Header
#define _Aft2d_Node_Header

#include <Pnt2d.hxx>
#include <Aft2d_NodeAdaptor.hxx>
#include <Aft_Node.hxx>
#include <handle.hxx>

namespace AutLib
{

	typedef Aft_Node<Pnt2d, Aft2d_NodeAdaptor> Aft2d_NodeBase;

	class Aft2d_Node
		: public Aft2d_NodeBase
	{

		typedef Aft2d_NodeBase base;
		typedef pHandle(Aft2d_Node) node_ptr;

		/*Private Data*/

	public:

		typedef base::ptType ptType;

		static const node_ptr null;

		static const Pnt2d& getCoord(Aft2d_Node* const& theNode)
		{
			Debug_Null_Pointer(theNode);
			return theNode->Coord();
		}

		static const Pnt2d& getCoord(const node_ptr& theNode)
		{
			Debug_Null_Pointer(theNode);
			return theNode->Coord();
		}

		Aft2d_Node()
		{}

		Aft2d_Node
		(
			const Standard_Integer theIndex
		)
			: base(theIndex)
		{}

		Aft2d_Node
		(
			const Standard_Integer theIndex,
			const Pnt2d& theCoord
		)
			: base(theIndex, theCoord)
		{}

		template<class T>
		void InsertToEntity(const T*)
		{
			FatalErrorIn("void InsertToEntity(const T*) ")
				<< " unsupported entity type attempts to insert to the entity list"
				<< abort(FatalError);
		}

		template<>
		void InsertToEntity<Aft2d_Edge>(const Aft2d_Edge* theEdge)
		{
			InsertToEdges(theEdge);
		}

		template<>
		void InsertToEntity<Aft2d_TriElement>(const Aft2d_TriElement* theElement)
		{
			InsertToElements(theElement);
		}

		template<class T>
		Standard_Boolean RemoveFromEntity(const T*)
		{
			FatalErrorIn("void RemoveFromEntity(const T*) ")
				<< " unsupported entity type attempts to remove from entity list"
				<< abort(FatalError);
		}

		template<>
		Standard_Boolean RemoveFromEntity<Aft2d_Edge>(const Aft2d_Edge* theEdge)
		{
			return RemoveFromEdges(theEdge);
		}

		template<>
		Standard_Boolean RemoveFromEntity<Aft2d_TriElement>(const Aft2d_TriElement* theElement)
		{
			return RemoveFromElements(theElement);
		}

		template<class T>
		void InsertToFront(const T*)
		{
			FatalErrorIn("void InsertToFront(const T*) ")
				<< " unsupported entity type attempts to insert to the front list"
				<< abort(FatalError);
		}

		template<>
		void InsertToFront<Aft2d_Edge>(const Aft2d_Edge* theEdge)
		{
			InsertToFrontEdges(theEdge);
		}

		template<class T>
		Standard_Boolean RemoveFromFront(const T*)
		{
			FatalErrorIn("Standard_Boolean RemoveFromFront(const T*) ")
				<< " unsupported entity type attempts to remove from the front list"
				<< abort(FatalError);
		}

		template<>
		Standard_Boolean RemoveFromFront<Aft2d_Edge>(const Aft2d_Edge* theEdge)
		{
			return RemoveFromFrontEdges(theEdge);
		}

		
	};
}

#endif // !_Aft2d_Node_Header
