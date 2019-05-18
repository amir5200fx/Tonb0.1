#pragma once
#ifndef _Solid_Paired_Header
#define _Solid_Paired_Header

#include <Pnt3d.hxx>
#include <Solid_Entity.hxx>
#include <OFstream.hxx>

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class Solid_Edge;

	template<class Point>
	class Entity_Polygon;

	typedef Entity_Polygon<Pnt3d> Entity3d_Polygon;

	class Solid_Paired
		: public Solid_Entity
		, public std::enable_shared_from_this<Solid_Paired>
	{

		typedef std::shared_ptr<Solid_Edge> edge_ptr;
		typedef std::shared_ptr<Entity3d_Polygon> polygon_ptr;

		/*Private Data*/

		edge_ptr theEdge0_;
		edge_ptr theEdge1_;

		polygon_ptr theMesh_;

	public:

		Solid_Paired
		(
			const Standard_Integer theIndex, 
			const word& theName,
			const edge_ptr& theEdge0,
			const edge_ptr& theEdge1
		)
			: Solid_Entity(theIndex, theName)
			, theEdge0_(theEdge0)
			, theEdge1_(theEdge1)
		{}

		Solid_Paired
		(
			const Standard_Integer theIndex,
			const edge_ptr& theEdge0,
			const edge_ptr& theEdge1
		)
			: Solid_Entity(theIndex)
			, theEdge0_(theEdge0)
			, theEdge1_(theEdge1)
		{}

		Solid_Paired
		(
			const edge_ptr& theEdge0,
			const edge_ptr& theEdge1
		)
			: theEdge0_(theEdge0)
			, theEdge1_(theEdge1)
		{}

		const edge_ptr& Edge0() const
		{
			return theEdge0_;
		}

		const edge_ptr& Edge1() const
		{
			return theEdge1_;
		}

		Standard_Boolean IsPaired() const
		{
			return theEdge0_ AND theEdge1_;
		}

		void ExportToPlt(std::fstream& File) const;

		void ExportToPlt(OFstream& File) const;
	};
}

#endif // !_Solid_Paired_Header
