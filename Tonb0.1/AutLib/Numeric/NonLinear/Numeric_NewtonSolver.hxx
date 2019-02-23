#pragma once
#ifndef _Numeric_NewtonSolver_Header
#define _Numeric_NewtonSolver_Header

#include <Standard_TypeDef.hxx>
#include <error.hxx>
#include <OSstream.hxx>

namespace AutLib
{

	enum Numeric_NewtonSolverCondition
	{
		Numeric_NewtonSolver_LevelExceeded = 0,
		Numeric_NewtonSolver_ZeroDivide,
		Numeric_NewtonSolver_Converged
	};

	class Numeric_NewtonSolverInfo
	{

		/*Private Data*/

		Numeric_NewtonSolverCondition theCondition_;

		Standard_Integer theMaxNbIters_;
		Standard_Integer theIter_;

		Standard_Real theTolerance_;
		Standard_Real theUR_;

		Standard_Real theResidual_;
		Standard_Real theResult_;
		Standard_Real theSmall_;
		Standard_Real theZero_;

		Standard_Boolean IsDone_;

	protected:

		void SetCondition(const Numeric_NewtonSolverCondition condition)
		{
			theCondition_ = condition;
		}

		void SetResidual(const Standard_Real theRes)
		{
			theResidual_ = theRes;
		}

		void SetResult(const Standard_Real theResult)
		{
			theResult_ = theResult;
		}

		void SetDone()
		{
			IsDone_ = Standard_True;
		}

		const Standard_Integer MaxNbIterations() const
		{
			return theMaxNbIters_;
		}

		const Standard_Integer Iter() const
		{
			return theIter_;
		}

		Standard_Integer& Iter()
		{
			return theIter_;
		}

		const Standard_Real Tolerance() const
		{
			return theTolerance_;
		}

		const Standard_Real UR() const
		{
			return theUR_;
		}

	public:

		static const Standard_Real DEFAULT_TOLERANCE;
		static const Standard_Real DEFAULT_UNDERRELAXATION;
		static const Standard_Integer DEFAULT_MAX_NB_ITERATIONS;
		static const Standard_Real DEFAULT_SMALL;
		static const Standard_Real DEFAULT_ZERO;

		Numeric_NewtonSolverInfo()
			: IsDone_(Standard_False)
			, theIter_(0)
			, theMaxNbIters_(DEFAULT_MAX_NB_ITERATIONS)
			, theTolerance_(DEFAULT_TOLERANCE)
			, theUR_(DEFAULT_UNDERRELAXATION)
			, theSmall_(DEFAULT_SMALL)
			, theZero_(DEFAULT_ZERO)
			, theResidual_(0)
		{}

		Numeric_NewtonSolverCondition Condition() const
		{
			return theCondition_;
		}

		Standard_Integer NbIterated() const
		{
			return Iter();
		}

		Standard_Real Residual() const
		{
			return theResidual_;
		}

		Standard_Real Result() const
		{
			return theResult_;
		}

		Standard_Real Small() const
		{
			return theSmall_;
		}

		Standard_Real& Small()
		{
			return theSmall_;
		}

		Standard_Real Zero() const
		{
			return theZero_;
		}

		Standard_Real& Zero()
		{
			return theZero_;
		}

		Standard_Boolean IsDone() const
		{
			return IsDone_;
		}

		void SetMaxNbIterations(const Standard_Integer theMaxNbIters)
		{
			theMaxNbIters_ = theMaxNbIters;
		}

		void SetTolerance(const Standard_Real theTol)
		{
			theTolerance_ = theTol;
		}

		void SetSmall(const Standard_Real theSmall)
		{
			theSmall_ = theSmall;
		}

		void SetZero(const Standard_Real theZero)
		{
			theZero_ = theZero;
		}

		void SetUnderRelaxation(const Standard_Real theUR)
		{
			theUR_ = theUR;
		}
	};

	template<class T>
	class Numeric_NewtonSolver
		: public Numeric_NewtonSolverInfo
	{

		/*Private Data*/

		const T& theobject_;

		Standard_Real(*theValueFunction_)(const Standard_Real, const T&);
		Standard_Real(*theDeriveFunction_)(const Standard_Real, const T&);

	public:

		Numeric_NewtonSolver(const T& object)
			: theobject_(object)
			, theValueFunction_(nullptr)
			, theDeriveFunction_(nullptr)
		{}

		Numeric_NewtonSolver
		(
			const T& object,
			Standard_Real(*theValueFunction)(const Standard_Real, const T&),
			Standard_Real(*theDeriveFunction)(const Standard_Real, const T&)
		)
			: theobject_(object)
			, theValueFunction_(theValueFunction)
			, theDeriveFunction_(theDeriveFunction)
		{}

		const Numeric_NewtonSolverInfo& Info() const
		{
			return *this;
		}

		Numeric_NewtonSolverInfo& Info()
		{
			return *this;
		}

		void Perform(const Standard_Real guess)
		{
			SetDone();

			Debug_Null_Pointer(theValueFunction_);
			Debug_Null_Pointer(theDeriveFunction_);

			const auto& object = *theobject_;

			Standard_Real y0 = theValueFunction_(guess, object);

			Standard_Real df, dp, p1, y1, rel_err, u;
			SetCondition(Numeric_NewtonSolver_LevelExceeded);

			u = guess;
			Iter() = 0;

			forThose(Iter, 1, MaxNbIterations())
			{
				Iter()++;

				df = theDeriveFunction_(u, object);

				if (ABS(df) == 0)
				{
					SetCondition(Numeric_NewtonSolver_ZeroDivide);
					dp = 0;
				}
				else
					dp = y0 / df;

				p1 = u - UR()*dp;
				y1 = theValueFunction_(p1, object);

				rel_err = 2.0 * ABS(dp) / (ABS(p1) + Small());

				if (rel_err < Tolerance() OR ABS(y1) < Zero())
					if (Condition() NOT_EQUAL Numeric_NewtonSolver_ZeroDivide) SetCondition(Numeric_NewtonSolver_Converged);

				u = p1;
				y0 = y1;

				if ((Standard_Integer)Condition())
					break;
			}

			SetResult(u);
			SetResidual(rel_err);
		}
	};
}

#endif // !_Numeric_NewtonSolver_Header
