#pragma once
#ifndef _Mesh_CurveIteration_Function_Header
#define _Mesh_CurveIteration_Function_Header

#include <Numeric_NewtonSolver.hxx>
#include <Mesh_CurveLength.hxx>
#include <Mesh_CurveEntity.hxx>

namespace AutLib
{

	// Forward Declarations
	template<class CurveType, class SizeMap>
	class Mesh_CurveEntity;

	template<class CurveType, class SizeMap>
	class Mesh_CurveIteration_Function
		: public Numeric_NewtonSolver_Function<true>
	{

		typedef Mesh_CurveEntity<CurveType, SizeMap> entity;

		/*Private Data*/

		const entity& theEntity_;

		Standard_Real theTolerance_;
		Standard_Real theX0_;
		Standard_Real theStep_;

	public:

		Mesh_CurveIteration_Function
		(
			const entity& theEntity,
			const Standard_Real theX0,
			const Standard_Real theStep,
			const Standard_Real theTol
		)
			: theEntity_(theEntity)
			, theX0_(theX0)
			, theStep_(theStep)
			, theTolerance_(theTol)
		{
			Lower() = theEntity.FirstParameter();
			Upper() = theEntity.LastParameter();
		}

		Mesh_CurveIteration_Function
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

		Standard_Real Tolerance() const
		{
			return theTolerance_;
		}

		Standard_Real X0() const
		{
			return theX0_;
		}

		Standard_Real Step() const
		{
			return theStep_;
		}

		void SetTolerance(const Standard_Real theTol)
		{
			theTolerance_ = theTol;
		}

		void SetX0(const Standard_Real x0)
		{
			theX0_ = x0;
		}

		void SetStep(const Standard_Real theStep)
		{
			theStep_ = theStep;
		}

		Standard_Real Value(const Standard_Real x) const override
		{
			return Mesh_CurveLength::Length<CurveType, SizeMap>(Entity(), X0(), x, Tolerance()) - Step();
		}
	};
}

#endif // !_Mesh_CurveIteration_Function_Header
