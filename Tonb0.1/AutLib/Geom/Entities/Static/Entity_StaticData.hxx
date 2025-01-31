#pragma once
#ifndef _Entity_StaticData_Header
#define _Entity_StaticData_Header

#include <Traits.hxx>
#include <Standard_TypeDef.hxx>
#include <OFstream.hxx>

#include <vector>
#include <memory>

namespace AutLib
{

	// Forward Declarations
	template<class Point> class Entity_Box;

	template<class Point, class Connectivity, bool NeighbData = false>
	class Entity_StaticData
	{

		typedef std::vector<Point> pointList;
		typedef std::vector<Connectivity> connectList;
		typedef Entity_Box<Point> box;
		typedef std::shared_ptr<box> box_ptr;

		/*Private Data*/

		pointList thePoints_;

		connectList theConnectivity_;

		box_ptr theBoundingBox_;

	public:

		typedef Point ptType;
		typedef Connectivity connectType;

		Entity_StaticData()
		{}

		Entity_StaticData
		(
			const pointList& thePoints,
			const connectList& theConnectivity
		)
			: thePoints_(thePoints)
			, theConnectivity_(theConnectivity)
		{}

		const pointList& Points() const
		{
			return thePoints_;
		}

		pointList& Points()
		{
			return thePoints_;
		}

		const connectList& Connectivity() const
		{
			return theConnectivity_;
		}

		connectList& Connectivity()
		{
			return theConnectivity_;
		}

		Standard_Integer NbPoints() const
		{
			return (Standard_Integer)thePoints_.size();
		}

		Standard_Integer NbConnectivity() const
		{
			return (Standard_Integer)theConnectivity_.size();
		}

		void CalcBoundingBox();

		const box_ptr& BoundingBox() const
		{
			return theBoundingBox_;
		}

		std::shared_ptr<Entity_StaticData> Merged(const Standard_Real theRes, const Standard_Real theRadius) const;

		void Transform(const typename transform_point_type<Point>::type& theTrasf)
		{
			for (auto& x : thePoints_)
			{
				x.Transform(theTrasf);
			}
		}

		void Merging(const Standard_Boolean HandleDegeneracy, const Standard_Real Resolution, const Standard_Real Radius);

		void ExportToPlt(std::fstream& File) const;

		void ExportToPlt(OFstream& File) const;
	};

	template<class Point, class Connectivity>
	class Entity_StaticData<Point, Connectivity, true>
		: public Entity_StaticData<Point, Connectivity, false>
	{

		typedef std::vector<Point> pointList;
		typedef std::vector<Connectivity> connectList;
		typedef Entity_Box<Point> box;
		typedef std::shared_ptr<box> box_ptr;

		/*Private Data*/

		connectList theNeighbors_;

	public:

		Entity_StaticData()
		{}

		Entity_StaticData
		(
			const pointList& thePoints,
			const connectList& theConnectivity,
			const connectList& theNeighbors
		)
			: Entity_StaticData<Point, Connectivity, false>(thePoints, theConnectivity)
			, theNeighbors_(theNeighbors)
		{}

		const connectList& Neighbors() const
		{
			return theNeighbors_;
		}

		connectList& Neighbors()
		{
			return theNeighbors_;
		}

		void Swap
		(
			const Standard_Integer theElement,
			const Standard_Integer theEdge
		);
	};
}

#endif // !_Entity_StaticData_Header
