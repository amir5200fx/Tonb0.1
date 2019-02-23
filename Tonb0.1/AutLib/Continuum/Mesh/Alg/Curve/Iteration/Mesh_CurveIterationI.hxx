#pragma once
#include <Global_Macros.hxx>
#include <Mesh_CurveLength.hxx>
#include <Numeric_NewtonSolver.hxx>
namespace AutLib
{
	template<class CurveEntity>
	inline Standard_Real IterValueAt(const Standard_Real X, const Mesh_CurveIteration<CurveEntity>& CurveIteration)
	{
		return
			Mesh_CurveLength<typename CurveEntity::curveType, typename CurveEntity::sizeMap>::CalcLength
			(
				CurveIteration.Entity(),
				CurveIteration.U0(),
				X,
				CurveIteration.Tolerance()
			) - CurveIteration.Step();
	}

	template<class CurveEntity>
	inline Standard_Real IterDeriveAt(const Standard_Real X, const Mesh_CurveIteration<CurveEntity>& CurveIteration)
	{
		return
			CurveEntity::Integrand
			(
				X,
				CurveIteration.Entity()
			);
	}
}

template<class CurveEntity>
inline Standard_Real AutLib::Mesh_CurveIteration<CurveEntity>::doIteration
(
	const Standard_Real theU0,
	const Standard_Real theGuess, 
	const Standard_Real theStep,
	const CurveEntity & theIntegrand
)
{
	Mesh_CurveIteration<CurveEntity> Iteration(theIntegrand, theU0, theStep);

	Numeric_NewtonSolver<Mesh_CurveIteration<CurveEntity>>
		Newton(Iteration, &IterValueAt, &IterDeriveAt);

	Newton.SetTolerance(Iteration.Tolerance());
	Newton.SetUnderRelaxation(Iteration.UnderRelaxation());
	Newton.Perform(theGuess);

	Debug_If_Condition_Message(NOT Newton.IsDone(), " Newton Algorithm is not performed");

	if (Newton.Condition() IS_EQUAL Numeric_NewtonSolver_ZeroDivide)
	{
		FatalErrorIn(FunctionSIG)
			<< "divide zero in Iterative function"
			<< AutLib::abort(FatalError);
	}

	if (Newton.Condition() IS_EQUAL Numeric_NewtonSolver_LevelExceeded)
	{
		IterFailedIn(FunctionSIG, Newton.NbIterated())
			<< "  Warning! LEVEL EXCEEDED encontered in Iterative function\n"
			<< "  no. of MAX ITERATION = " << Newton.NbIterated() << "\n"
			<< "  Residual = " << Newton.Residual() << "\n"
			<< AutLib::abort(IterFail);

	}
	return Newton.Result();
}

template<class CurveEntity>
inline Standard_Real AutLib::Mesh_CurveIteration<CurveEntity>::doIteration
(
	const Standard_Real guess,
	const Mesh_CurveIteration & info
)
{
	Numeric_NewtonSolver<Mesh_CurveIteration<CurveEntity>>
		Newton(info, &IterValueAt, &IterDeriveAt);

	Newton.SetTolerance(info.Tolerance());
	Newton.SetUnderRelaxation(info.UnderRelaxation());
	Newton.Perform(guess);

	Debug_If_Condition_Message(NOT Newton.IsDone(), " Newton Algorithm is not performed");

	if (Newton.Condition() IS_EQUAL Numeric_NewtonSolver_ZeroDivide)
	{
		FatalErrorIn(FunctionSIG)
			<< "divide zero in Iterative function"
			<< AutLib::abort(FatalError);
	}

	if (Newton.Condition() IS_EQUAL Numeric_NewtonSolver_LevelExceeded)
	{
		IterFailedIn(FunctionSIG, Newton.NbIterated())
			<< "  Warning! LEVEL EXCEEDED encontered in Iterative function\n"
			<< "  no. of MAX ITERATION = " << Newton.NbIterated() << "\n"
			<< "  Residual = " << Newton.Residual() << "\n"
			<< AutLib::abort(IterFail);

	}
	return Newton.Result();
}

template<class CurveEntity>
inline Standard_Real AutLib::Mesh_CurveIteration<CurveEntity>::operator()
(
	const Standard_Real theU0, 
	const Standard_Real theGuess, 
	const Standard_Real theStep, 
	const CurveEntity & theEntity
	)
{
	return Mesh_CurveIteration<CurveEntity>::doIteration(theU0, theGuess, theStep, theEntity);
}

template<class CurveEntity>
inline Standard_Real AutLib::Mesh_CurveIteration<CurveEntity>::operator()
(
	const Standard_Real theU0, 
	const Standard_Real theGuess, 
	const Standard_Real theStep, 
	const CurveEntity & theEntity, 
	const Standard_Real theTol, 
	const Standard_Real theUR
	)
{
	Mesh_CurveIteration<CurveEntity> Iteration(theEntity, theU0, theStep);
	Iteration.SetTolerance(theTol);
	Iteration.SetUR(theUR);
	return Mesh_CurveIteration<CurveEntity>::doIteration(theGuess, Iteration);
}

template<class CurveEntity>
inline Standard_Real AutLib::Mesh_CurveIteration<CurveEntity>::Perform
(
	const Standard_Real theGuess
)
{
	Numeric_NewtonSolver<Mesh_CurveIteration<CurveEntity>>
		Newton(*this, &IterValueAt, &IterDeriveAt);

	Newton.SetTolerance(Tolerance());
	Newton.SetUnderRelaxation(UnderRelaxation());
	Newton.Perform(theGuess);

	Debug_If_Condition_Message(NOT Newton.IsDone(), " Newton Algorithm is not performed");

	if (Newton.Condition() IS_EQUAL Numeric_NewtonSolver_ZeroDivide)
	{
		FatalErrorIn(FunctionSIG)
			<< "divide zero in Iterative function"
			<< AutLib::abort(FatalError);
	}

	if (Newton.Condition() IS_EQUAL Numeric_NewtonSolver_LevelExceeded)
	{
		IterFailedIn(FunctionSIG, Newton.NbIterated())
			<< "  Warning! LEVEL EXCEEDED encontered in Iterative function\n"
			<< "  no. of MAX ITERATION = " << Newton.NbIterated() << "\n"
			<< "  Residual = " << Newton.Residual() << "\n"
			<< AutLib::abort(IterFail);

	}
	return Newton.Result();
}