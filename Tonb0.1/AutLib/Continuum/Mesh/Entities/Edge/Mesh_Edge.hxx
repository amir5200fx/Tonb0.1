#pragma once
#ifndef _Mesh_Edge_Header
#define _Mesh_Edge_Header

#include <Global_Macros.hxx>
#include <Mesh_Entity.hxx>
#include <handle.hxx>

namespace AutLib
{

	template<class NodeType, class EdgeAdaptor>
	class Mesh_Edge
		: public Mesh_Entity
		, public EdgeAdaptor
	{

		typedef pHandle(NodeType) nodeType_ptr;
		typedef typename NodeType::ptType Point;

		/*Private Data*/

		nodeType_ptr theNode0_;
		nodeType_ptr theNode1_;

		//- Disallow Bitwise copy constructor and copy assignment
		DisallowBitWiseCopy(Mesh_Edge);

	public:

		typedef NodeType nodeType;

		Mesh_Edge()
		{}

		Mesh_Edge
		(
			const Standard_Integer theIndex
		)
			: Mesh_Entity(theIndex)
		{}

		Mesh_Edge
		(
			const Standard_Integer theIndex,
			const nodeType_ptr& theNode0,
			const nodeType_ptr& theNode1
		)
			: Mesh_Entity(theIndex)
			, theNode0_(theNode0)
			, theNode1_(theNode1)
		{}

		void Init
		(
			const Standard_Integer theIndex,
			const nodeType_ptr& theNode0,
			const nodeType_ptr& theNode1
		)
		{
			Mesh_Entity::SetIndex(theIndex);
			theNode0_ = theNode0;
			theNode1_ = theNode1;
		}

		void Init
		(
			const nodeType_ptr& theNode0,
			const nodeType_ptr& theNode1
		)
		{
			theNode0_ = theNode0;
			theNode1_ = theNode1;
		}

		const nodeType_ptr& Node0() const
		{
			return theNode0_;
		}

		nodeType_ptr& Node0()
		{
			return theNode0_;
		}

		const nodeType_ptr& Node1() const
		{
			return theNode1_;
		}

		nodeType_ptr& Node1()
		{
			return theNode1_;
		}

		const nodeType_ptr& Node(const Standard_Integer theIndex) const
		{
			return (&theNode0_)[theIndex];
		}

		nodeType_ptr& Node(const Standard_Integer theIndex)
		{
			return (&theNode0_)[theIndex];
		}

		void Get
		(
			nodeType_ptr& theNode0,
			nodeType_ptr& theNode1
		) const
		{
			theNode0 = theNode0_;
			theNode1 = theNode1_;
		}

		void SetNode0(const nodeType_ptr& theNode)
		{
			Node0() = theNode;
		}

		void SetNode1(const nodeType_ptr& theNode)
		{
			Node1() = theNode;
		}

		void Reverse()
		{
			std::swap(theNode0_, theNode1_);
		}
	};
}

#endif // !_Mesh_Edge_Header
