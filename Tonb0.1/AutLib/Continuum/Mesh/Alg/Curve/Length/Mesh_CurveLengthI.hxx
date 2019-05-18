#pragma once
#include <Numeric_AdaptIntegration.hxx>
#include <Mesh_CurveLength_Function.hxx>
#include <Mesh_CurveLength_GlobalInfo.hxx>
#include <NonConvergency_Iteration_Failure.hxx>
namespace AutLib
{

	template<class CurveType, class SizeMap>
	Standard_Real Mesh_CurveLength::Length
	(
		const Mesh_CurveEntity<CurveType, SizeMap>& theCurve, 
		const Standard_Real theLower, 
		const Standard_Real theUpper, 
		const Standard_Real theTolerance
	)
	{
		CurveInfo::AdaptInfo.Tolerance() = theTolerance;

		Numeric_AdaptIntegration<Mesh_CurveLength_Function<CurveType, SizeMap>>
			Integration(theCurve, theLower, theUpper, CurveInfo::AdaptInfo);

		Integration.Perform();

		if (NOT CurveInfo::AdaptInfo.IsDone())
		{
			FatalErrorIn("Standard_Real Mesh_CurveLength::Length()")
				<< "Intgeration is not dine!" << endl
				<< abort(FatalError);
		}

		if (NOT CurveInfo::AdaptInfo.IsConverged())
		{
			IterFailedIn(FunctionSIG, CurveInfo::AdaptInfo.NbInitIterations())
				<< "Algorithm is not converged!" << endl
				<< abort(FatalError);
		}

		return CurveInfo::AdaptInfo.Result();
	}
}