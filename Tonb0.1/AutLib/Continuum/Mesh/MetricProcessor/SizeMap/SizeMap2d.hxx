#pragma once
#ifndef _SizeMap2d_Header
#define _SizeMap2d_Header

#include <Pnt2d.hxx>
#include <gp_Vec2d.hxx>
#include <Entity2d_Box.hxx>

namespace AutLib
{

	// Forward Declarations
	class Aft2d_Edge;

	class SizeMap2d
	{

	public:

		typedef Pnt2d ptType;

		virtual Standard_Real BaseElementSize() const = 0;

		virtual Standard_Real CalcElementSize
		(
			const Pnt2d&
		) const = 0;

		virtual Standard_Real CalcElementSize
		(
			const Aft2d_Edge&
		) const = 0;

		virtual Standard_Real Oriented
		(
			const Pnt2d&, 
			const Aft2d_Edge&
		) const = 0;

		virtual Standard_Real CalcDistance
		(
			const Pnt2d&, 
			const Pnt2d&
		) const = 0;

		virtual Standard_Real CalcSquareDistance
		(
			const Pnt2d&,
			const Pnt2d&
		) const = 0;

		virtual Standard_Real CalcDistance
		(
			const Pnt2d&,
			const Aft2d_Edge&
		) const = 0;

		virtual Standard_Real CalcSquareDistance
		(
			const Pnt2d&, 
			const Aft2d_Edge&
		) const = 0;

		virtual Standard_Real CalcUnitDistance
		(
			const Pnt2d&,
			const Pnt2d&
		) const = 0;

		virtual Pnt2d CalcOptimumCoord
		(
			const Standard_Real theSize, 
			const Aft2d_Edge&
		) const = 0;

		virtual Pnt2d CalcCentreOf
		(
			const Pnt2d&,
			const Pnt2d&
		) const = 0;

		virtual Entity2d_Box CalcSearchRegion
		(
			const Standard_Real theRadius, 
			const Pnt2d& theCentre
		) const = 0;

		virtual Entity2d_Box CalcSearchRegion
		(
			const Standard_Real theRadius, 
			const Pnt2d& theCentre,
			const Aft2d_Edge&
		) const = 0;

		virtual Standard_Real Integrand
		(
			const Pnt2d& thePoint, 
			const Pnt2d& theVector
		) const = 0;

		virtual Standard_Real Integrand
		(
			const Pnt2d& thePoint,
			const gp_Vec2d& theVector
		) const = 0;

		virtual Standard_Real IntegrandPerSize
		(
			const Pnt2d& thePoint, 
			const Pnt2d& theVector
		) const = 0;

		virtual Standard_Real IntegrandPerSize
		(
			const Pnt2d& thePoint,
			const gp_Vec2d& theVector
		) const = 0;
	};
}

#endif // !_SizeMap_Header
