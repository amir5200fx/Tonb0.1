#pragma once
#ifndef _Mesh_CurveEntity_Header
#define _Mesh_CurveEntity_Header

#include <Standard_Handle.hxx>
#include <Global_Named.hxx>
#include <Global_Indexed.hxx>
#include <TypeTraits.hxx>

#include <memory>

namespace AutLib
{

	template<class CurveType, class SizeMap>
	class Mesh_CurveEntity
		: public Global_Named
		, public Global_Indexed
	{

		typedef typename CurveType::ptType Point;

		/*Private Data*/

		const SizeMap& theSizeMap_;
		
		const CurveType& theCurve_;

		Standard_Real theFirst_;
		Standard_Real theLast_;

	public:

		typedef CurveType curveType;
		typedef SizeMap sizeMap;

		/*template<class U = Standard_Real>
		static resolvedType<is_two_dimension<CurveType::dim>::value, U>
			Intergrand(const Standard_Real p, const Mesh_CurveEntity& theEntity);

		template<class U = Standard_Real>
		static resolvedType<is_three_dimension<CurveType::dim>::value, U>
			Intergrand(const Standard_Real p, const Mesh_CurveEntity& theEntity);*/

		static Standard_Real Integrand
		(
			const Standard_Real theParam,
			const Mesh_CurveEntity& theEntity
		)
		{
			auto first = theEntity.First();
			auto last = theEntity.Last();

			auto param = theParam;
			if (param < first) param = first;
			if (param > last) param = last;

			typename CurveType::ptType point;
			typename CurveType::vtType vector;

			theEntity.Curve().D1(param, point, vector);
			return theEntity.Map().Integrand(point, Point(vector.XY()));
		}

		Mesh_CurveEntity
		(
			const CurveType& theCurve,
			const SizeMap& theSizeMap,
			const Standard_Real theFirst,
			const Standard_Real theLast
		)
			: theCurve_(theCurve)
			, theSizeMap_(theSizeMap)
			, theFirst_(theFirst)
			, theLast_(theLast)
		{}

		Mesh_CurveEntity
		(
			const CurveType& theCurve,
			const SizeMap& theSizeMap
		)
			: theCurve_(theCurve)
			, theSizeMap_(theSizeMap)
		{}

		const SizeMap& Map() const
		{
			return theSizeMap_;
		}

		const CurveType& Curve() const
		{
			return theCurve_;
		}

		const Standard_Real First() const
		{
			return theFirst_;
		}

		Standard_Real First()
		{
			return theFirst_;
		}

		const Standard_Real Last() const
		{
			return theLast_;
		}

		Standard_Real& Last()
		{
			return theLast_;
		}

		Point Value(const Standard_Real x) const
		{
			return theCurve_.Value(x);
		}
	};
}

#include <Mesh_CurveEntityI.hxx>

#endif // !_Mesh_CurveEntity_Header
