#pragma once
#ifndef _Mesh_CurveIteration_Derivation_Header
#define _Mesh_CurveIteration_Derivation_Header

#include <Numeric_NewtonSolver.hxx>
#include <Mesh_CurveEntity.hxx>

namespace AutLib
{

	template<class CurveType, class SizeMap>
	class Mesh_CurveIteration_Derivation
		: public Numeric_NewtonSolver_Derivation<true>
	{

		typedef Mesh_CurveEntity<CurveType, SizeMap> entity;

		/*Private Data*/

		const entity& theEntity_;

	public:

		Mesh_CurveIteration_Derivation
		(
			const entity& theEntity
		)
			: theEntity_(theEntity)
		{
			Lower() = theEntity.FirstParameter();
			Upper() = theEntity.LastParameter();
		}

		const entity& Entity() const
		{
			return theEntity_;
		}

		Standard_Real Value(const Standard_Real x) const override
		{
			return Mesh_CurveEntity<CurveType, SizeMap>::Integrand(x, Entity());
		}
	};
}

#endif // !_Mesh_CurveIteration_Derivation_Header
