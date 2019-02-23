#pragma once
#ifndef _Mesh_Curve_Header
#define _Mesh_Curve_Header

#include <Standard_Handle.hxx>
#include <Mesh_CurveEntity.hxx>
#include <Mesh_CurveCorrectGuess.hxx>
#include <Mesh_CurveIteration.hxx>

#include <memory>

namespace AutLib
{

	class Mesh_CurveIntegrationInfo
	{

		/*Private Data*/

		Standard_Real theTolerance_;

	public:

		static const Standard_Real DEFAULT_TOLERANCE;

		Mesh_CurveIntegrationInfo()
			: theTolerance_(DEFAULT_TOLERANCE)
		{}

		Standard_Real Tolerance() const
		{
			return theTolerance_;
		}

		Standard_Real& Tolerance()
		{
			return theTolerance_;
		}

		void SetTolerance(const Standard_Real theTol)
		{
			theTolerance_ = theTol;
		}

	};

	template<class CurveEntity>
	class Mesh_Curve
		: public Mesh_CurveIntegrationInfo
	{

		/*Private Data*/

		Mesh_CurveCorrectGuess<CurveEntity> theCorrector_;

		Mesh_CurveIteration<CurveEntity> theIterator_;

		const CurveEntity& theEntity_;

	public:

		Mesh_Curve(const CurveEntity& theEntity)
			: theIterator_(theEntity)
			, theEntity_(theEntity)
		{}

		const Mesh_CurveCorrectGuessInfo& CorrectorInfo() const
		{
			return theCorrector_.Info();
		}

		Mesh_CurveCorrectGuessInfo& CorrectorInfo()
		{
			return theCorrector_.Info();
		}

		const Mesh_CurveIterationInfo& IteratorInfo() const
		{
			return theIterator_.Info();
		}

		Mesh_CurveIterationInfo& IteratorInfo()
		{
			return theIterator_.Info();
		}

		const Mesh_CurveIntegrationInfo& IntegrationInfo() const
		{
			return *this;
		}

		Mesh_CurveIntegrationInfo& IntegrationInfo()
		{
			return *this;
		}

		void Perform();
	};
}

#include <Mesh_CurveI.hxx>

#endif // !_Mesh_Curve_Header
