#pragma once
#ifndef _Mesh_Curve_Header
#define _Mesh_Curve_Header

#include <Mesh_CurveEntity.hxx>
#include <Entity_Connectivity.hxx>
#include <Entity_StaticData.hxx>

#include <memory>
#include <vector>

namespace AutLib
{

	class Mesh_CurveInfo
	{

		/*Private Data*/

		Standard_Integer theNbCorrections_;

		Standard_Real theUR_;
		Standard_Real theIntegTol_;
		Standard_Real theCorrectionTol_;

		Standard_Boolean IsDone_;

	protected:

		Standard_Boolean& Change_IsDone()
		{
			return IsDone_;
		}

	public:

		static const Standard_Real DEFAULT_UNDER_RELAXATION;
		static const Standard_Real DEFAULT_INTG_TOLERANCE;
		static const Standard_Integer DEFAULT_MAX_SUBDIVIDE_CURVE;

		static const Standard_Real DEFAULT_CORRECT_TOLERANCE;
		static const Standard_Integer DEFAULT_NB_CORRECTIONS;

		Mesh_CurveInfo()
			: theUR_(DEFAULT_UNDER_RELAXATION)
			, theIntegTol_(DEFAULT_INTG_TOLERANCE)
			, theCorrectionTol_(DEFAULT_CORRECT_TOLERANCE)
			, theNbCorrections_(DEFAULT_NB_CORRECTIONS)
			, IsDone_(Standard_False)
		{}

		Standard_Boolean IsDone() const
		{
			return IsDone_;
		}

		Standard_Real UnderRelaxation() const
		{
			return theUR_;
		}

		Standard_Real Tolerance() const
		{
			return theIntegTol_;
		}

		Standard_Real CorrectTolerance() const
		{
			return theCorrectionTol_;
		}

		Standard_Integer NbCorrections() const
		{
			return theNbCorrections_;
		}

		void SetUR(const Standard_Real theUR)
		{
			theUR_ = theUR;
		}
	};

	template<class CurveType, class SizeMap>
	class Mesh_Curve
		: public Mesh_CurveInfo
	{

		typedef typename SizeMap::ptType Point;

		typedef Entity_StaticData<Point, connectivity::dual> chain;
		typedef std::shared_ptr<chain> chain_ptr;
		typedef std::vector<Standard_Real> realList;

		/*Private Data*/

		const SizeMap& theMap_;

		const CurveType& theCurve_;

		Standard_Real theFirst_;
		Standard_Real theLast_;

		chain_ptr theChain_;

		void MakeChain(const realList& theParameters);

	public:

		Mesh_Curve
		(
			const CurveType& theCurve,
			const SizeMap& theMap,
			const Standard_Real theFirst,
			const Standard_Real theLast
		)
			: theCurve_(theCurve)
			, theMap_(theMap)
			, theFirst_(theFirst)
			, theLast_(theLast)
		{}

		const chain_ptr& Mesh() const
		{
			return theChain_;
		}

		void Perform();

		void ExportToPlt(OFstream& File) const;
	};
}

#include <Mesh_CurveI.hxx>

#endif // !_Mesh_Curve_Header
