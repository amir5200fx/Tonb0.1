#pragma once
#ifndef _Solid_Wire_Header
#define _Solid_Wire_Header

#include <Pnt3d.hxx>
#include <Solid_Entity.hxx>
#include <Entity2d_BoxFwd.hxx>

#include <vector>
#include <memory>

namespace AutLib
{

	// Forward Declarations
	class Solid_Edge;
	class Solid_Vertex;

	class Solid_Wire
		: public Solid_Entity
		, public std::enable_shared_from_this<Solid_Wire>
	{

		typedef std::shared_ptr<Solid_Edge> edge_ptr;
		typedef std::vector<edge_ptr> edgeList;
		typedef std::shared_ptr<edgeList> edgeList_ptr;
		typedef std::shared_ptr<Solid_Vertex> vertex_ptr;
		typedef std::vector<vertex_ptr> vertexList;

		/*Private Data*/

		edgeList_ptr theEdges_;

		void CheckWire();

	public:

		Solid_Wire
		(
			const edgeList_ptr& theEdges
		)
			: theEdges_(theEdges)
		{
			CheckWire();
		}

		Solid_Wire
		(
			const Standard_Integer theIndex,
			const word& theName,
			const edgeList_ptr& theEdges
		)
			: Solid_Entity(theIndex, theName)
			, theEdges_(theEdges)
		{
			CheckWire();
		}

		Solid_Wire
		(
			const Standard_Integer theIndex,
			const edgeList_ptr& theEdges
		)
			: Solid_Entity(theIndex)
			, theEdges_(theEdges)
		{
			CheckWire();
		}

		Standard_Integer NbEdges() const
		{
			Debug_Null_Pointer(theEdges_);
			return (Standard_Integer)theEdges_->size();
		}

		Entity2d_Box CalcParametricBoundingBox() const;

		const edgeList_ptr& Edges() const
		{
			return theEdges_;
		}

		void Reverse();

		void RetrieveVerticesTo(vertexList& theVertices) const;

		void ExportToPlt(std::fstream& File) const;
	};
}

#endif // !_Solid_Wire_Header
