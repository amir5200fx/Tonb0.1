#pragma once
#ifndef _Mesh_CurveIteration_Header
#define _Mesh_CurveIteration_Header

#include <Mesh_CurveEntity.hxx>

namespace AutLib
{

	struct Mesh_CurveIterationInfo
	{
		Standard_Real theIntegTol;
		Standard_Real theIterTol;
		Standard_Real theUR;

		Mesh_CurveIterationInfo()
			: theIntegTol(1.0E-2)
			, theIterTol(1.0E-8)
			, theUR(0.9)
		{}
	};

	class Mesh_CurveIteration
	{

	public:

		template<class CurveType, class SizeMap>
		static Standard_Real Iteration
		(
			const Standard_Real Start,
			const Standard_Real Guess,
			const Standard_Real Step, 
			const Mesh_CurveEntity<CurveType, SizeMap>& theCurve, 
			const Mesh_CurveIterationInfo& theInfo
		);

	};
}

#include <Mesh_CurveIterationI.hxx>

#endif // !_Mesh_CurveIteration_Header
