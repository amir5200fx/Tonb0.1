#pragma once
#ifndef _Aft2d_Header
#define _Aft2d_Header

#include <Geom_PriorityList.hxx>
#include <Aft_Core.hxx>
#include <Aft2d_FrontInfo.hxx>

namespace AutLib
{

	template
		<
		template<class> class GeomSearch,
		template<class> class SizeMap
		>
	class Aft2d
		: public Aft_Core
		<
		Aft2d_FrontInfo,
		GeomSearch,
		Geom_PriorityList,
		SizeMap
		>
	{

		typedef typename Aft2d_FrontInfo::frontType frontType;
		typedef Aft_Core
			<
			Aft2d_FrontInfo,
			GeomSearch,
			Geom_PriorityList,
			SizeMap
			> core;
		typedef SizeMap<frontType> sizeMap;
		typedef std::shared_ptr<SizeMap<frontType>> sizeMap_ptr;

	public:

		Aft2d(const std::shared_ptr<SizeMap<frontType>>& theSizeMap)
			: core(theSizeMap)
		{}
	};
}

#endif // !_Aft2d_Header
