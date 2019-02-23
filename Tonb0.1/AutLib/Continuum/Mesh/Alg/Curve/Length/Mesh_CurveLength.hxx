#pragma once
#ifndef _Mesh_CurveLength_Header
#define _Mesh_CurveLength_Header

#include <Mesh_CurveEntity.hxx>
#include <Numeric_AdptIntegral.hxx>
#include <NonConvergency_Iteration_Failure.hxx>

namespace AutLib
{

	template<class CurveEntity>
	class Mesh_CurveLength
	{

	public:

		static Standard_Real CalcLength
		(
			const CurveEntity& theEntity,
			const Standard_Real theLower,
			const Standard_Real theUpper,
			const Standard_Real theTolerance
		)
		{
			Numeric_AdptIntegral<CurveEntity>
				Integral
				(
					theEntity,
					&CurveEntity::Integrand,
					theLower,
					theUpper
				);

			Integral.Tolerance() = theTolerance;

			Integral.NbInitIterations() = 4;
			Integral.Perform();

			Debug_If_Condition_Message(NOT Integral.IsDone(), " Integral not performed");

			if (NOT Integral.IsConverged())
			{
				IterFailedIn(FunctionSIG, Integral.MaxNbIterations())
					<< "Integral not converged"
					<< AutLib::abort(IterFail);
			}
			return Integral.Result();
		}

		static Standard_Real CalcLength
		(
			const CurveEntity& theEntity,
			const Standard_Real theTolerance
		)
		{
			return CalcLength(theEntity, theEntity.First(), theEntity.Last(), theTolerance);
		}
	};
}

#endif // !_Mesh_CurveLength_Header
