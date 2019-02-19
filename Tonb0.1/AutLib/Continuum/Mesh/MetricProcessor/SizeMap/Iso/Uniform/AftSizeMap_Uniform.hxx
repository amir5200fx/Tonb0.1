#pragma once
#ifndef _AftSizeMap_Uniform_Header
#define _AftSizeMap_Uniform_Header

#include <Aft_SizeMap.hxx>
#include <error.hxx>
#include <OSstream.hxx>

namespace AutLib
{

	template<class FrontEntity>
	class AftSizeMap_Uniform
		: public Aft_SizeMap<FrontEntity>
	{

		template< bool cond, typename U >
		using resolvedType = typename std::enable_if< cond, U >::type;

		/*Private Data*/

		Standard_Real theSize_;
		Standard_Real theInvSize_;

	public:

		typedef typename FrontEntity::nodeType::ptType Point;

		explicit AftSizeMap_Uniform(const Standard_Real theSize)
		{}

		void InitElementSize(const Standard_Real theSize)
		{
			if (theSize <= RealSmall())
			{
				FatalErrorIn(FunctionSIG)
					<< "Invalid Size element"
					<< abort(FatalError);
			}

			theInvSize_ = (Standard_Real)1.0 / BaseElementSize();
		}

		void SetSizeElement(const Standard_Real theSize)
		{
			InitElementSize(theSize);
		}

		Standard_Real BaseElementSize() const override
		{
			return theSize_;
		}

		Standard_Real CalcElementSize(const Point&) const override
		{
			return theSize_;
		}

		Standard_Real CalcElementSize(const FrontEntity& theEntity) const override
		{
			return CalcElementSize(theEntity.Centre());
		}

		Standard_Real Oriented 
		(
			const Point& theCoord,
			const FrontEntity& theEntity
		) const override
		{
			return theEntity.Oriented(theCoord);
		}

		Standard_Real CalcDistance
		(
			const Point& theP0,
			const Point& theP1
		) const override
		{
			return theP0.Distance(theP1);
		}

		Standard_Real CalcSquareDistance
		(
			const Point& theP0,
			const Point& theP1
		) const override
		{
			return theP0.SquareDistance(theP1);
		}

		/*typename std::enable_if<is_validType<FrontEntity, (int)FrontEntity::rank, 3>::value, Standard_Real>::type
			CalcDistance
			(
				const Point& theCoord,
				const typename sub_Type
				<
				FrontEntity,
				(int)FrontEntity::rank - 1
				>::type& theEntity
			) const override
		{
			return theEntity.CalcDistance(theCoord);
		}

		typename std::enable_if<is_validType<FrontEntity, (int)FrontEntity::rank, 3>::value, Standard_Real>::type
			CalcSquareDistance
			(
				const Point& theCoord,
				const typename sub_Type
				<
				FrontEntity,
				(int)FrontEntity::rank - 1
				>::type& theEntity
			) const override
		{
			return theEntity.CalcSquareDistance(theCoord);
		}*/

		template<class U = Standard_Real>
		resolvedType
			<
			is_validType<FrontEntity, (int)FrontEntity::rank, 3>::value, U
			>
			CalcDistance
			(
				const Point& theCoord,
				const typename sub_Type
				<
				FrontEntity,
				(int)FrontEntity::rank - 1
				>::type& theEntity
			) const
		{
			return theEntity.CalcDistance(theCoord);
		}

		template<class U = Standard_Real>
		resolvedType
			<
			is_validType<FrontEntity, (int)FrontEntity::rank, 3>::value, U
			>
			CalcSquareDistance
			(
				const Point& theCoord,
				const typename sub_Type
				<
				FrontEntity,
				(int)FrontEntity::rank - 1
				>::type& theEntity
			) const
		{
			return theEntity.CalcSquareDistance(theCoord);
		}

		Point CalcOptimumCoord
		(
			const Standard_Real theSize,
			const FrontEntity& theEntity
		) const override
		{
			return theEntity.CalcOptimumCoord(theSize);
		}

		Entity_Box<Point> CalcSearchRegion
		(
			const Standard_Real theRadius,
			const Point& theCentre
		) const override
		{
			return Entity_Box<Point>::Box(theCentre, theRadius);
		}

		Entity_Box<Point> CalcSearchRegion
		(
			const Standard_Real theRadius,
			const Point& theCentre,
			const FrontEntity&
		) const override
		{
			return Entity_Box<Point>::Box(theCentre, theRadius);
		}
	};
}

#endif // !_AftSizeMap_Uniform_Header
