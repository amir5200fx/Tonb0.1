#pragma once
#include <Pnt2d.hxx>
#include <Geom2d_Curve.hxx>
namespace AutLib
{

	/*template<class CurveType, class SizeMap>
	template<class U>
	inline Mesh_CurveEntity<CurveType, SizeMap>::resolvedType<is_two_dimension<CurveType::dim>::value, U> 
		Mesh_CurveEntity<CurveType, SizeMap>::Intergrand(const Standard_Real p, const Mesh_CurveEntity & theEntity)
	{
		Debug_Null_Pointer(theEntity.Map());
		Debug_Null_Pointer(theEntity.Curve());

		auto first = theEntity.First();
		auto last = theEntity.Last();
		auto param = p;
		if (param < first) param = first;
		if (param > last) param = last;

		gp_Pnt2d point;
		gp_Vec2d vector;

		const Geom2d_Curve& curve = *theEntity.Curve();
		curve.D1(param, point, vector);

		return theEntity.Map()->Integrand(point, Pnt2d(vector.XY()));
	}*/
}