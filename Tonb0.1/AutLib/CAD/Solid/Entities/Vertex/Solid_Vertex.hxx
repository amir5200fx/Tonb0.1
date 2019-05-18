#pragma once
#ifndef _Solid_Vertex_Header
#define _Solid_Vertex_Header

#include <Pnt3d.hxx>
#include <Adt_AvlTree.hxx>
#include <Solid_Entity.hxx>
#include <Cad_EntityPrecision.hxx>

#include <memory>
#include <vector>

namespace AutLib
{

	// Forward Declarations
	class Solid_Edge;
	class Solid_Face;

	class Solid_Vertex
		: public Solid_Entity
		, public Cad_EntityPrecision
		, public std::enable_shared_from_this<Solid_Vertex>
	{

		typedef std::weak_ptr<Solid_Edge> edge_ptr;
		typedef std::weak_ptr<Solid_Face> face_ptr;
		typedef std::vector<edge_ptr> edgeList;
		typedef std::vector<face_ptr> faceList;

		/*Private Data*/

		Pnt3d theCoord_;

		Adt_AvlTree<edge_ptr> theEdges_;
		Adt_AvlTree<face_ptr> theFaces_;

		void SetComparableFunction();

	public:

		typedef Pnt3d ptType;

		Solid_Vertex
		(
			const Standard_Integer theIndex
		)
			: Solid_Entity(theIndex)
		{
			SetComparableFunction();
		}

		Solid_Vertex
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: Solid_Entity(theIndex, theName)
		{
			SetComparableFunction();
		}

		Solid_Vertex
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Pnt3d& theCoord
		)
			: Solid_Entity(theIndex, theName)
			, theCoord_(theCoord)
		{
			SetComparableFunction();
		}

		Solid_Vertex
		(
			const Standard_Integer theIndex,
			const Pnt3d& theCoord
		)
			: Solid_Entity(theIndex)
			, theCoord_(theCoord)
		{
			SetComparableFunction();
		}

		const Pnt3d& Coord() const
		{
			return theCoord_;
		}

		Pnt3d& Coord()
		{
			return theCoord_;
		}

		Standard_Integer NbEdges() const
		{
			return theEdges_.Size();
		}

		Standard_Integer NbFaces() const
		{
			return theFaces_.Size();
		}

		Standard_Integer NbRings() const;

		Standard_Boolean IsOrphan() const
		{
			return theEdges_.IsEmpty();
		}

		std::shared_ptr<Solid_Vertex> This()
		{
			return shared_from_this();
		}

		std::shared_ptr<const Solid_Vertex> This() const
		{
			return shared_from_this();
		}

		void ImportToEdges(const edge_ptr& theEdge)
		{
			theEdges_.Insert(theEdge);
		}

		void ImportToEdges_dup(const edge_ptr& theEdge)
		{
			theEdges_.InsertIgnoreDup(theEdge);
		}

		void ImportToFaces(const face_ptr& theFace)
		{
			theFaces_.Insert(theFace);
		}

		void ImportToFaces_dup(const face_ptr& theFace)
		{
			theFaces_.InsertIgnoreDup(theFace);
		}

		void RemoveFromtEdges(const edge_ptr& theEdge)
		{
			theEdges_.Remove(theEdge);
		}

		void RemoveFromFaces(const face_ptr& theFace)
		{
			theFaces_.Remove(theFace);
		}

		void RetrieveEdgesTo(edgeList& theList) const
		{
			theEdges_.RetrieveTo(theList);
		}

		void RetrieveFacesTo(faceList& theList) const
		{
			theFaces_.RetrieveTo(theList);
		}
	};
}

#endif // !_Solid_Vertex_Header
