#pragma once
#ifndef _Aft_Core_Header
#define _Aft_Core_Header

#include <Mesh_GlobalData.hxx>
#include <Aft_FrontGlobalData.hxx>
#include <Mesh_TypeTraits.hxx>

namespace AutLib
{

	template
		<
		class FrontInfo,
		template<class> class GeomSearch,
		template<class> class PriorityList,
		template<class> class SizeMap
		>
	class Aft_Core
		: public FrontInfo
		, public Mesh_GlobalData<typename FrontInfo::elementType>
		, public SizeMap<typename FrontInfo::frontType>
		, public Aft_FrontGlobalData<typename FrontInfo::frontType, GeomSearch, PriorityList>
	{

	protected:

		typedef Mesh_GlobalData<typename FrontInfo::elementType>
			globalData;
		typedef FrontInfo frontInfo;
		typedef Aft_FrontGlobalData<typename FrontInfo::frontType, GeomSearch, PriorityList>
			frontData;
		typedef typename FrontInfo::frontType frontType;
		typedef typename FrontInfo::nodeType nodeType;
		typedef typename nodeType::ptType Point;
		typedef SizeMap<typename FrontInfo::frontType>
			sizeMap;

		typedef pHandle(frontType) front_Ptr;
		typedef pHandle(nodeType) node_Ptr;

		typedef typename sub_Type<frontType, (int)frontType::rank - 1>::type subType;
		typedef pHandle(subType) subType_Ptr;

		template< bool cond, typename U >
		using resolvedType = typename std::enable_if< cond, U >::type;

	private:

		/*Private Data*/

	public:
	};
}

#endif // !_Aft_Core_Header
