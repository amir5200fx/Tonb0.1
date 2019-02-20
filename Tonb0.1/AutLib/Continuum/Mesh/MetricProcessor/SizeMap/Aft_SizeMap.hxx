#pragma once
#ifndef _Aft_SizeMap_Header
#define _Aft_SizeMap_Header

#include <Entity2d_Box.hxx>
#include <Entity3d_Box.hxx>
#include <Mesh_TypeTraits.hxx>

namespace AutLib
{

	// Forward Declarations
	
	template<class FrontEntity>
	class Aft_SizeMap
	{

		template< bool cond, typename U >
		using resolvedType = typename std::enable_if< cond, U >::type;

	public:

		typedef typename FrontEntity::nodeType::ptType Point;

		virtual Standard_Real BaseElementSize() const = 0;

		virtual Standard_Real CalcElementSize(const Point&) const = 0;

		virtual Standard_Real CalcElementSize(const FrontEntity&) const = 0;

		virtual Standard_Real Oriented(const Point&, const FrontEntity&) const = 0;

		virtual Standard_Real CalcDistance(const Point&, const Point&) const = 0;

		virtual Standard_Real CalcSquareDistance(const Point&, const Point&) const = 0;

		virtual Standard_Real CalcDistance(const Point&, const FrontEntity&) const = 0;

		virtual Standard_Real CalcSquareDistance(const Point&, const FrontEntity&) const = 0;

		/*virtual
			typename std::enable_if<is_validType<FrontEntity, (int)FrontEntity::rank, 3>::value, Standard_Real>::type
			CalcDistance
			(
				const Point& theCoord,
				const typename sub_Type
				<
				FrontEntity,
				(int)FrontEntity::rank - 1
				>::type& theEntity
			) const = 0;

		virtual
			typename std::enable_if<is_validType<FrontEntity, (int)FrontEntity::rank, 3>::value, Standard_Real>::type
			CalcSquareDistance
			(
				const Point& theCoord,
				const typename sub_Type
				<
				FrontEntity,
				(int)FrontEntity::rank - 1
				>::type& theEntity
			) const = 0;*/

		/*template<class U = Standard_Real>
		virtual resolvedType
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
			) const = 0;

		template<class U = Standard_Real>
		virtual resolvedType
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
			) const = 0;*/

		virtual Point CalcOptimumCoord(const Standard_Real theSize, const FrontEntity&) const = 0;

		virtual Entity_Box<Point> CalcSearchRegion(const Standard_Real theRadius, const Point& theCentre) const = 0;

		virtual Entity_Box<Point> CalcSearchRegion(const Standard_Real theRadius, const Point& theCentre, const FrontEntity&) const = 0;
	};
}

#endif // !_Aft_SizeMap_Header
