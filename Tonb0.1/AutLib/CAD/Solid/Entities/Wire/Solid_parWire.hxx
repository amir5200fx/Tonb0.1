#pragma once
#ifndef _Solid_parWire_Header
#define _Solid_parWire_Header

#include <Pnt2d.hxx>
#include <Solid_Entity.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <vector>
#include <memory>

namespace AutLib
{

	// Forward Declarations
	class Solid_parEdge;
	template<class T> class Entity_Box;

	typedef Entity_Box<Pnt2d> Entity2d_Box;

	struct Solid_parWireTolerance
	{
		Standard_Real Tolerance;

		Solid_parWireTolerance();
	};

	class Solid_parWire
		: public Solid_Entity
		, public std::enable_shared_from_this<Solid_parWire>
		, public Solid_parWireTolerance
	{

		typedef std::shared_ptr<Solid_parEdge> edge_ptr;
		typedef std::vector<edge_ptr> edgeList;
		typedef std::shared_ptr<edgeList> edgeList_ptr;

		/*Private Data*/

		edgeList_ptr theEdges_;

		void CheckWire();

	public:

		Solid_parWire(const edgeList_ptr& theCurves)
			: theEdges_(theCurves)
		{
			CheckWire();
		}

		Solid_parWire
		(
			const Standard_Integer theIndex,
			const word& theName,
			const edgeList_ptr& theCurves
		)
			: Solid_Entity(theIndex, theName)
			, theEdges_(theCurves)
		{
			CheckWire();
		}

		Solid_parWire
		(
			const Standard_Integer theIndex,
			const edgeList_ptr& theCurves
		)
			: Solid_Entity(theIndex)
			, theEdges_(theCurves)
		{
			CheckWire();
		}

		Standard_Integer NbEdges() const
		{
			Debug_Null_Pointer(theEdges_);
			return (Standard_Integer)theEdges_->size();
		}

		Entity2d_Box CalcParametricBoundingBox() const;

		const edgeList& Edges() const
		{
			Debug_Null_Pointer(theEdges_);
			return *theEdges_;
		}


	};
}

#endif // !_Solid_parWire_Header
