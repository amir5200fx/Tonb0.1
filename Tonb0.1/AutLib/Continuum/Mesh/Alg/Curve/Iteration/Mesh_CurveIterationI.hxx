#pragma once
#include <Mesh_CurveIteration_Function.hxx>
#include <Mesh_CurveIteration_Derivation.hxx>
#include <Numeric_NewtonSolver.hxx>
#include <Mesh_CurveIteration_GlobalInfo.hxx>
namespace AutLib
{

	template<class CurveType, class SizeMap>
	Standard_Real Mesh_CurveIteration::Iteration
	(
		const Standard_Real Start, 
		const Standard_Real Guess, 
		const Standard_Real Step,
		const Mesh_CurveEntity<CurveType, SizeMap>& theCurve,
		const Mesh_CurveIterationInfo& theInfo
	)
	{
		CurveInfo::NewtonInfo.SetUnderRelaxation(theInfo.theUR);
		CurveInfo::NewtonInfo.Tolerance() = theInfo.theIterTol;

		Mesh_CurveIteration_Function<CurveType, SizeMap> Fun(theCurve, Start, Step, theInfo.theIntegTol);
		Mesh_CurveIteration_Derivation<CurveType, SizeMap> Der(theCurve);

		Numeric_NewtonSolver
			<
			Mesh_CurveIteration_Function<CurveType, SizeMap>,
			Mesh_CurveIteration_Derivation<CurveType, SizeMap>,
			true
			>
			Iterator(Fun, Der, CurveInfo::NewtonInfo);

		Iterator.Perform(Guess);

		Debug_If_Condition_Message(NOT CurveInfo::NewtonInfo.IsDone(), "Newton's Algorithm is not performed");

		if (CurveInfo::NewtonInfo.Condition() IS_EQUAL NewtonIter_ZERODIVIDE)
		{
			FatalErrorIn("Standard_Real Mesh_CurveIteration::Iteration()")
				<< "divide zero in Iterative function" << endl
				<< abort(FatalError);
		}

		if (CurveInfo::NewtonInfo.Condition() IS_EQUAL NewtonIter_LEVEL_EXCEEDED)
		{
			FatalErrorIn("Standard_Real Mesh_CurveIteration::Iteration()")
				<< "LEVEL EXCEEDED encontered in Iterative function" << endl
				<< abort(FatalError);
		}
		return CurveInfo::NewtonInfo.Result();
	}
}