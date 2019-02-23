#pragma once
#ifndef _Numeric_AdptIntegral_Header
#define _Numeric_AdptIntegral_Header

#include <Standard_TypeDef.hxx>
#include <Stl_Vector.hxx>
#include <error.hxx>
#include <OSstream.hxx>

namespace AutLib
{

	class Numeric_AdptIntegral_Bound
	{

		/*Private Data*/

		Standard_Real theLower_;
		Standard_Real theUpper_;

	public:

		Numeric_AdptIntegral_Bound
		(
			const Standard_Real theLower = 0.,
			const Standard_Real theUpper = 0.
		)
			: theLower_(theLower)
			, theUpper_(theUpper)
		{}

		Standard_Real Lower() const
		{
			return theLower_;
		}

		Standard_Real& Lower()
		{
			return theLower_;
		}

		Standard_Real Upper() const
		{
			return theUpper_;
		}

		Standard_Real& Upper()
		{
			return theUpper_;
		}

		void SetLower(const Standard_Real theLower)
		{
			theLower_ = theLower;
		}

		void SetUpper(const Standard_Real theUpper)
		{
			theUpper_ = theUpper;
		}
	};

	class Numeric_AdptIntegralBase
	{

		/*private Data*/

		Standard_Boolean IsDone_;
		Standard_Boolean IsConverged_;

		Standard_Real theTolerance_;
		Standard_Real theResult_;

		Standard_Integer theMaxIters_;
		Standard_Integer theInitialIter_;

	protected:

		Standard_Boolean& Change_IsDone()
		{
			return IsDone_;
		}

		Standard_Boolean& Change_IsConverged()
		{
			return IsConverged_;
		}

		Standard_Real& ChangeResult()
		{
			return theResult_;
		}

	public:

		static const Standard_Real DEFAULT_TOLERANCE;
		static const Standard_Integer DEFAULT_MAX_ITERATIONS;
		static const Standard_Integer DEFAULT_INIT_ITERATIONS;

		Numeric_AdptIntegralBase()
			: IsDone_(Standard_False)
			, IsConverged_(Standard_False)
			, theTolerance_(DEFAULT_TOLERANCE)
			, theMaxIters_(DEFAULT_MAX_ITERATIONS)
			, theInitialIter_(DEFAULT_INIT_ITERATIONS)
			, theResult_(0)
		{}

		Standard_Boolean IsDone() const
		{
			return IsDone_;
		}

		Standard_Boolean IsConverged() const
		{
			return IsConverged_;
		}

		Standard_Real Tolerance() const
		{
			return theTolerance_;
		}

		Standard_Real& Tolerance()
		{
			return theTolerance_;
		}

		Standard_Real Result() const
		{
			return theResult_;
		}

		Standard_Integer MaxNbIterations() const
		{
			return theMaxIters_;
		}

		Standard_Integer& MaxNbIterations()
		{
			return theMaxIters_;
		}

		Standard_Integer NbInitIterations() const
		{
			return theInitialIter_;
		}

		Standard_Integer& NbInitIterations()
		{
			return theInitialIter_;
		}
	};

	template<class IntegrandObject>
	class Numeric_AdptIntegral
		: public Numeric_AdptIntegral_Bound
		, public Numeric_AdptIntegralBase
	{

		typedef Numeric_AdptIntegralBase setup;

		typedef Stl_Vector<Standard_Real> realList;
		typedef Stl_Vector<Standard_Integer> intList;

		/*Private Data*/

		static const Standard_Integer RESERVED = 10;

		const IntegrandObject& theObject_;

		Standard_Real(*theIntegrand_)(const Standard_Real, const IntegrandObject&);

	public:

		Numeric_AdptIntegral(const IntegrandObject& object)
			: theObject_(object)
		{}

		Numeric_AdptIntegral
		(
			const IntegrandObject& object,
			Standard_Real(*Integrand)(const Standard_Real, const IntegrandObject&)
		)
			: theObject_(object)
			, theIntegrand_(Integrand)
		{}

		Numeric_AdptIntegral
		(
			const IntegrandObject& object,
			Standard_Real(*Integrand)(const Standard_Real, const IntegrandObject&),
			const Standard_Real Lower,
			const Standard_Real Upper
		)
			: theObject_(object)
			, theIntegrand_(Integrand)
			, Numeric_AdptIntegral_Bound(Lower, Upper)
		{}

		void Perform()
		{
			if (Lower() IS_EQUAL Upper())
			{
				FatalErrorIn(" void Perform()")
					<< " Invalid Integration domain"
					<< abort(FatalError);
			}

			setup::Change_IsDone() = Standard_True;

			auto U0 = Lower();
			auto U1 = Upper();
			auto MaxSize = setup::MaxNbIterations() + RESERVED;

			realList
				tol(MaxSize),
				a(MaxSize),
				h(MaxSize),
				FA(MaxSize),
				FC(MaxSize),
				FB(MaxSize),
				S(MaxSize);

			intList L(MaxSize);

			auto APP = (Standard_Real)0.;
			auto i = (Standard_Integer)1;

			tol[i] = (Standard_Real)10.0 * setup::Tolerance();
			a[i] = U0;
			h[i] = (Standard_Real)0.5*(U1 - U0);

			const auto& Integrand = *theIntegrand_;
			const auto& Object = theObject_;

			FA[i] = Integrand(U0, Object);
			FC[i] = Integrand(U0 + h[i], Object);
			FB[i] = Integrand(U1, Object);

			S[i] = h[i] * (FA[i] + (Standard_Real)4.0*FC[i] + FB[i]) / (Standard_Real)3.0;

			L[i] = 1;

			Standard_Real FD, FE, S1, S2;
			Standard_Real v1, v2, v3, v4, v5, v6, v7;
			Standard_Integer v8;
			Standard_Integer k = 0;

			Standard_Real C6 = (Standard_Real)1.0 / (Standard_Real)6.0;

			while (i > 0)
			{
				FD = Integrand(a[i] + (Standard_Real)0.5*h[i], Object);
				FE = Integrand(a[i] + (Standard_Real)1.5*h[i], Object);

				S1 = h[i] * (FA[i] + (Standard_Real)4.0 * FD + FC[i]) * C6;
				S2 = h[i] * (FC[i] + (Standard_Real)4.0 * FE + FB[i]) * C6;

				v1 = a[i];
				v2 = FA[i];
				v3 = FC[i];
				v4 = FB[i];
				v5 = h[i];
				v6 = tol[i];
				v7 = S[i];
				v8 = L[i];

				i--;

				k++;

				if (ABS(S1 + S2 - v7) < v6)
				{
					APP += (S1 + S2);
				}
				else
				{
					if (v8 >= setup::MaxNbIterations() + 1)
					{
						setup::Change_IsConverged() = Standard_False;

						setup::ChangeResult() = APP;

						return;
					}
					else
					{
						i++;

						a[i] = v1 + v5;
						FA[i] = v3;
						FC[i] = FE;
						FB[i] = v4;
						h[i] = (Standard_Real)0.5*v5;
						tol[i] = (Standard_Real)0.5*v6;
						S[i] = S2;
						L[i] = v8 + 1;

						i++;

						a[i] = v1;
						FA[i] = v2;
						FC[i] = FD;
						FB[i] = v3;
						h[i] = h[i - 1];
						tol[i] = tol[i - 1];
						S[i] = S1;
						L[i] = L[i - 1];
					}
				}
			}

			setup::ChangeResult() = APP;
			setup::Change_IsConverged() = Standard_True;
		}


	};
}

#endif // !_Numeric_AdptIntegral_Header
