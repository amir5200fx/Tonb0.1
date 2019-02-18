#pragma once
namespace AutLib
{
	inline Geom_PrQuadrant CalcQuadrant
	(
		const Pnt2d & theCoord,
		const Pnt2d & theCentre
	)
	{
		if (theCoord.X() <= theCentre.X())
			if (theCoord.Y() <= theCentre.Y())
				return Geom_PrQuadrant_SW;
			else
				return Geom_PrQuadrant_NW;
		else
		{
			if (theCoord.Y() <= theCentre.Y())
				return Geom_PrQuadrant_SE;
			else
				return Geom_PrQuadrant_NE;
		}
	}
}