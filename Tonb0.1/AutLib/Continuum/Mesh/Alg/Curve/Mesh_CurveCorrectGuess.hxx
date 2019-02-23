#pragma once
#ifndef _Mesh_CurveCorrectGuess_Header
#define _Mesh_CurveCorrectGuess_Header

#include <Standard_TypeDef.hxx>
#include <Mesh_CurveEntity.hxx>

namespace AutLib
{

	class Mesh_CurveCorrectGuessInfo
	{

		/*Private Data*/

		Standard_Real theTolerance_;

		Standard_Integer theNbIterations_;

		Standard_Real theUmin_;
		Standard_Real theUmax_;

		Standard_Real theResult_;

	protected:

		Standard_Integer NbIterations() const
		{
			return theNbIterations_;
		}

		Standard_Real Tolerance() const
		{
			return theTolerance_;
		}

		Standard_Real Umin() const
		{
			return theUmin_;
		}

		Standard_Real Umax() const
		{
			return theUmax_;
		}

		void SetResult(const Standard_Real theRes)
		{
			theResult_ = theRes;
		}

	public:

		static const Standard_Real DEFAULT_TOLERANCE;
		static const Standard_Integer DEFAULT_NB_ITERATIONS;

		Mesh_CurveCorrectGuessInfo()
			: theTolerance_(DEFAULT_TOLERANCE)
			, theNbIterations_(DEFAULT_NB_ITERATIONS)
		{}

		Standard_Real Result() const
		{
			return theResult_;
		}
		
		void SetTolerance(const Standard_Real theTol)
		{
			theTolerance_ = theTol;
		}

		void SetNbIterations(const Standard_Integer theNbIters)
		{
			theNbIterations_ = theNbIters;
		}

		void SetUmin(const Standard_Real theU0)
		{
			theUmin_ = theU0;
		}

		void SetUmax(const Standard_Real theU1)
		{
			theUmax_ = theU1;
		}
	};

	template<class CurveEntity>
	class Mesh_CurveCorrectGuess
		: public Mesh_CurveCorrectGuessInfo
	{

		/*Private Data*/

		

	public:

		Mesh_CurveCorrectGuess()
		{}

		void Perform
		(
			const Standard_Real U0, 
			const Standard_Real Guess, 
			const CurveEntity& theEntity
		)
		{
			const auto& map = theEntity.Map();
			const auto& curve = theEntity.Curve();

			Standard_Real Correct = Guess;
			Pnt2d P0 = theEntity.Value(U0);

			forThose(Iter, 1, NbIterations())
			{
				auto Dis = map.CalcUnitDistance(P0, curve.Value(Correct));
				Correct = U0 + (Correct - U0) / Dis;

				if (Correct < Umin()) Correct = Umin();
				if (Correct > Umax()) Correct = Umax();

				if (ABS(1.0 - Dis) < Tolerance()) break;
			}
			SetResult(Correct);
		}

		const Mesh_CurveCorrectGuessInfo& Info() const
		{
			return *this;
		}

		Mesh_CurveCorrectGuessInfo& Info()
		{
			return *this;
		}

	};
}

#endif // !_Mesh_CurveCorrectGuess_Header
