#pragma once
#ifndef _Mesh_CurveLength_Header
#define _Mesh_CurveLength_Header

#include <Mesh_CurveEntity.hxx>

namespace AutLib
{

	class Mesh_CurveLength
	{

	public:

		template<class CurveType, class SizeMap>
		static Standard_Real Length
		(
			const Mesh_CurveEntity<CurveType, SizeMap>& theCurve,
			const Standard_Real theLower,
			const Standard_Real theUpper,
			const Standard_Real theTolerance
		);

		template<class CurveType, class SizeMap>
		static Standard_Real Length
		(
			const Mesh_CurveEntity<CurveType, SizeMap>& theCurve,
			const Standard_Real theTolerance
		)
		{
			return Length(theCurve, theCurve.FirstParameter(), theCurve.LastParameter(), theTolerance);
		}
	};
}

#include <Mesh_CurveLengthI.hxx>

#endif // !_Mesh_CurveLength_Header
