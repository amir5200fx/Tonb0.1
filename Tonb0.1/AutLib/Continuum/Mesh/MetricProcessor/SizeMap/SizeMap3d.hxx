#pragma once
#ifndef _SizeMap3d_Header
#define _SizeMap3d_Header

#include <Pnt3d.hxx>
#include <Entity3d_Box.hxx>

namespace AutLib
{

	// Forward Declarations
	class Aft3d_Facet;
	class Aft3d_Edge;

	class SizeMap3d
	{

	public:

		virtual Standard_Real BaseElementSize() const = 0;

		virtual Standard_Real CalcElementSize(const Aft3d_Facet&) const = 0;

		virtual Standard_Real CalcElementSize(const Pnt3d&) const = 0;

		virtual Standard_Real Oriented
		(
			const Pnt3d&,
			const Aft3d_Facet&
		) const = 0;

		virtual Standard_Real CalcDistance
		(
			const Pnt3d&,
			const Pnt3d&
		) const = 0;

		virtual Standard_Real CalcSquareDistance
		(
			const Pnt3d&,
			const Pnt3d&
		) const = 0;

		virtual Standard_Real CalcDistance
		(
			const Pnt3d&,
			const Aft3d_Facet&
		) const = 0;

		virtual Standard_Real CalcSquareDistance
		(
			const Pnt3d&,
			const Aft3d_Facet&
		) const = 0;

		virtual Standard_Real CalcDistance
		(
			const Pnt3d&,
			const Aft3d_Edge&
		) const = 0;

		virtual Standard_Real CalcSquareDistance
		(
			const Pnt3d&,
			const Aft3d_Edge&
		) const = 0;

		virtual Standard_Real CalcDistance
		(
			const Aft3d_Edge&,
			const Aft3d_Edge&
		) const = 0;

		virtual Standard_Real CalcSquareDistance
		(
			const Aft3d_Edge&,
			const Aft3d_Edge&
		) const = 0;

		virtual Standard_Real CalcUnitDistance(const Pnt3d&, const Pnt3d&) const = 0;

		//virtual Pnt3d CalcOptimumCoord(const Standard_Real theSize, const Aft3d_Facet&) const = 0;

		//virtual Entity3d_Box CalcSearchRegion(const Standard_Real theRadius, const Pnt3d& theCentre) const = 0;
	};
}

#endif // !_SizeMap3d_Header
