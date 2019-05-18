#pragma once
#include <Mesh_CurveLength.hxx>
#include <Mesh_CurveIteration.hxx>
#include <GeoProcessor.hxx>
namespace AutLib
{

	template<class CurveType, class SizeMap>
	void Mesh_Curve<CurveType, SizeMap>::MakeChain(const realList & theParameters)
	{
		theChain_ = std::make_shared<chain>();

		auto& Points = theChain_->Points();
		Points.reserve(theParameters.size());

		for (const auto x : theParameters)
		{
			Points.push_back(theCurve_.Value(x));
		}

		Standard_Integer K = 0;
		auto& Indices = theChain_->Connectivity();
		Indices.resize(theParameters.size() - 1);
		for (auto& x : Indices)
		{
			x.Value(0) = K + 1;
			x.Value(1) = K + 2;
			++K;
		}
	}

	namespace MeshLib
	{
		template<class CurveType, class SizeMap>
		static Standard_Real CorrectGuess
		(
			const Standard_Real U0,
			const Standard_Real Guess, 
			const Standard_Real theUmin, 
			const Standard_Real theUmax, 
			const Standard_Real theTol, 
			const Mesh_CurveEntity<CurveType, SizeMap>& theCurve, 
			const Standard_Integer NbLevels
		)
		{
			const auto& map = theCurve.SizeMap();
			const auto& curve = theCurve.Curve();

			auto Correct = Guess;
			auto P0 = curve.Value(U0);

			forThose(Iter, 1, NbLevels)
			{
				auto dis = map.CalcUnitDistance(P0, curve.Value(Correct));
				Correct = U0 + (Correct - U0) / dis;

				if (Correct < theUmin) Correct = theUmin;
				if (Correct > theUmax) Correct = theUmax;

				if (ABS(1.0 - dis) < theTol) break;
			}
			return Correct;
		}

		template<class CurveType, class SizeMap>
		static Standard_Real CalcLength
		(
			const Mesh_CurveEntity<CurveType, SizeMap>& theCurve,
			const Standard_Real theTol,
			const Standard_Integer Current,
			const Standard_Integer MaxLevels
		)
		{
			try
			{
				return Mesh_CurveLength::Length(theCurve, theTol);
			}
			catch (NonConvergency_Iteration_Failure&)
			{
				if (Current > MaxLevels)
				{
					FatalErrorIn(FunctionSIG)
						<< "Can not Calculate length of the curve" << endl
						<< abort(FatalError);
				}
				return CalcLength
				(
					Mesh_CurveEntity<CurveType, SizeMap>
					(
						theCurve.Curve(), 
						theCurve.SizeMap(),
						theCurve.FirstParameter(),
						MEAN(theCurve.FirstParameter(), theCurve.LastParameter())
						),
					theTol, 
					Current + 1,
					MaxLevels
				)
					+ 
					CalcLength
					(
						Mesh_CurveEntity<CurveType, SizeMap>
						(
							theCurve.Curve(),
							theCurve.SizeMap(),
							MEAN(theCurve.FirstParameter(), theCurve.LastParameter()), theCurve.LastParameter()
							),
						theTol, 
						Current + 1, 
						MaxLevels
					);
			}
		}

		template<class CurveType, class SizeMap>
		static Standard_Real CalcLength
		(
			const Mesh_CurveEntity<CurveType, SizeMap>& theCurve,
			const Standard_Real theTol
		)
		{
			return CalcLength(theCurve, theTol, 0, Mesh_CurveInfo::DEFAULT_MAX_SUBDIVIDE_CURVE);
		}
	}

	template<class CurveType, class SizeMap>
	void Mesh_Curve<CurveType, SizeMap>::Perform()
	{
		Mesh_CurveEntity<CurveType, SizeMap> Integrand(theCurve_, theMap_, theFirst_, theLast_);

		// Determine the Length of the curve under the current space function
		auto curveLength = MeshLib::CalcLength(Integrand, Tolerance());

		// uniform nb. of segment under the current space function
		auto NbSegments = MAX(Processor::Round(curveLength*(1.0 + EPS6)), Processor::Round(curveLength*(1.0 - EPS6)));

		// There must be atleast one segment
		if (NbSegments < 1) NbSegments = 1;
		Debug_If_Condition(NbSegments < 1);

		const auto Ds = curveLength / (Standard_Real)NbSegments;
		const auto dt = 1.0 / curveLength;
		Standard_Real U0, U1, Guess;

		std::vector<Standard_Real> Parameters(NbSegments + 1);

		Parameters[0] = theFirst_;
		Parameters[Parameters.size() - 1] = theLast_;

		U0 = Parameters[0];
		Guess = U0 + dt;  // Debug: 4/14/2018

		if (Guess < theFirst_) Guess = theFirst_;
		if (Guess > theLast_) Guess = theLast_;

		Mesh_CurveIterationInfo info;
		//info.theUR = UR();

		forThose
		(
			Index,
			1,
			NbSegments - 1
		)
		{
			Guess = MeshLib::CorrectGuess
			(
				U0,
				Guess,
				theFirst_,
				theLast_,
				CorrectTolerance(),
				Integrand,
				NbCorrections()
			);

			U1 = Mesh_CurveIteration::Iteration(U0, Guess, Ds, Integrand, info);

			if (NOT INSIDE(U1, theFirst_, theLast_))
			{
				FatalErrorIn("void Mesh_Curve<CurveType, SizeMap>::Perform()")
					<< "Invalid Parameter: " << U1 << endl
					<< " - First parameter: " << theFirst_ << endl
					<< " - Last parameter: " << theLast_ << endl
					<< abort(FatalError);
			}

			Parameters[Index] = U1;

			Guess = U1 + MIN(dt, UnderRelaxation()*(Parameters[Index] - Parameters[Index - 1]));

			Debug_If_Condition(Guess <= U1);

			U0 = U1;
		}

		MakeChain(Parameters);

		Change_IsDone() = Standard_True;
	}

}