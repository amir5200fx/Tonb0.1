#pragma once
#ifndef _Mesh_CurveIteration_Header
#define _Mesh_CurveIteration_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{

	class Mesh_CurveIterationInfo
	{

		/*Private Data*/

		Standard_Real theU0_;
		Standard_Real theStep_;

		Standard_Real theTolerance_;
		Standard_Real theUR_;  // under relaxation factor

	public:

		static const Standard_Real DEFAULT_TOLERANCE;
		static const Standard_Real DEFAULT_UNDER_RELAXATION;

		Mesh_CurveIterationInfo()
			: theTolerance_(DEFAULT_TOLERANCE)
			, theUR_(DEFAULT_UNDER_RELAXATION)
		{}

		Mesh_CurveIterationInfo
		(
			const Standard_Real theU0,
			const Standard_Real theStep
		)
			: theU0_(theU0)
			, theStep_(theStep)
			, theTolerance_(DEFAULT_TOLERANCE)
			, theUR_(DEFAULT_UNDER_RELAXATION)
		{}

		Standard_Real U0() const
		{
			return theU0_;
		}

		Standard_Real& U0()
		{
			return theU0_;
		}

		const Standard_Real Step() const
		{
			return theStep_;
		}

		Standard_Real& Step()
		{
			return theStep_;
		}

		Standard_Real Tolerance() const
		{
			return theTolerance_;
		}

		Standard_Real& Tolerance()
		{
			return theTolerance_;
		}

		Standard_Real UnderRelaxation() const
		{
			return theUR_;
		}

		Standard_Real& UnderRelaxation()
		{
			return theUR_;
		}

		void SetU0(const Standard_Real theU0)
		{
			theU0_ = theU0;
		}

		void SetStep(const Standard_Real theStep)
		{
			theStep_ = theStep;
		}

		void SetTolerance(const Standard_Real theTol)
		{
			theTolerance_ = theTol;
		}

		void SetUR(const Standard_Real theUr)
		{
			theUR_ = theUr;
		}
	};

	template<class CurveEntity>
	class Mesh_CurveIteration
		: public Mesh_CurveIterationInfo
	{

		/*Private Data*/

		const CurveEntity& theEntity_;

	public:


		static Standard_Real doIteration
		(
			const Standard_Real theU0,
			const Standard_Real theGuess,
			const Standard_Real theStep,
			const CurveEntity& theIntegrand
		);

		static Standard_Real doIteration
		(
			const Standard_Real guess,
			const Mesh_CurveIteration& info
		);

		Mesh_CurveIteration
		(
			const CurveEntity& theEntity
		)
			: theEntity_(theEntity)
		{}

		Mesh_CurveIteration
		(
			const CurveEntity& theEntity,
			const Standard_Real theU0,
			const Standard_Real theStep
		)
			: theEntity_(theEntity)
			, Mesh_CurveIterationInfo(theU0, theStep)
		{}

		Standard_Real operator()
			(
				const Standard_Real theU0,
				const Standard_Real theGuess, 
				const Standard_Real theStep,
				const CurveEntity& theEntity
				);

		Standard_Real operator()
			(
				const Standard_Real theU0,
				const Standard_Real theGuess,
				const Standard_Real theStep,
				const CurveEntity& theEntity,
				const Standard_Real theTol,
				const Standard_Real theUR
				);

		const CurveEntity& Entity() const
		{
			return theEntity_;
		}

		const Mesh_CurveIterationInfo& Info() const
		{
			return *this;
		}

		Mesh_CurveIterationInfo& Info()
		{
			return *this;
		}

		Standard_Real Perform(const Standard_Real theGuess);
	};
}

#include <Mesh_CurveIterationI.hxx>

#endif // !_Mesh_CurveIteration_Header
