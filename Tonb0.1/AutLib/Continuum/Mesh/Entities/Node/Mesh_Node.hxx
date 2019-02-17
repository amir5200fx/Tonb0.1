#pragma once
#ifndef _Mesh_Node_Header
#define _Mesh_Node_Header

#include <Global_Macros.hxx>
#include <Mesh_Entity.hxx>

namespace AutLib
{

	template<class Point, class NodeAdaptor>
	class Mesh_Node
		: public Mesh_Entity
		, public NodeAdaptor
	{

		/*Private Data*/

		//- Coordinate of the node
		Point theCoord_;

		DisallowBitWiseCopy(Mesh_Node);

	public:

		typedef Point ptType;

		static const Mesh_Node null;

		Mesh_Node()
		{}

		Mesh_Node
		(
			const Standard_Integer theIndex
		)
			: Mesh_Entity(theIndex)
		{}

		Mesh_Node
		(
			const Standard_Integer theIndex,
			const Point& theCoord
		)
			: Mesh_Entity(theIndex)
			, theCoord_(theCoord)
		{}

		const Point& Coord() const
		{
			return theCoord_;
		}

		Point& Coord()
		{
			return theCoord_;
		}

		void SetCoord(const Point& theCoord)
		{
			theCoord_ = theCoord;
		}
	};
}

#endif // !_Mesh_Node_Header
