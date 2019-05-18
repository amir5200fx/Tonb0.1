#pragma once
#ifndef _Entity_Polygon_Header
#define _Entity_Polygon_Header

#include <Standard_TypeDef.hxx>
#include <OFstream.hxx>

#include <vector>
#include <fstream>

namespace AutLib
{

	template<class Point>
	class Entity_Polygon
	{

		typedef std::vector<Point> pointList;

		/*Private Data*/

		pointList thePoints_;

		Standard_Real theDeflection_;

	public:

		Entity_Polygon()
		{}

		Entity_Polygon
		(
			const pointList& thePoints,
			const Standard_Real theDeflection
		)
			: thePoints_(thePoints)
			, theDeflection_(theDeflection)
		{}

		Entity_Polygon Reversed() const
		{
			Entity_Polygon copy = *this;
			copy.Reverse();
			return std::move(copy);
		}

		const pointList& Points() const
		{
			return thePoints_;
		}

		pointList& Points()
		{
			return thePoints_;
		}

		Standard_Real Deflection() const
		{
			return theDeflection_;
		}

		Standard_Real& Deflection()
		{
			return theDeflection_;
		}

		Standard_Integer NbPoints() const
		{
			return (Standard_Integer)thePoints_.size();
		}

		Standard_Boolean IsClosed() const;

		void Reverse();

		void Smoothing(const Standard_Real Omega, const Standard_Integer NbIterations);

		void ExportToPlt(std::fstream& File) const;

		void ExportToPlt(OFstream& File) const;
	};
}

#endif // !_Entity_Polygon_Header
