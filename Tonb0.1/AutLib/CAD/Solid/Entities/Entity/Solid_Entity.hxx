#pragma once
#ifndef _Solid_Entity_Header
#define _Solid_Entity_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Cad_EntityPrecision.hxx>

namespace AutLib
{

	class Solid_Entity
		: public Global_Indexed
		, public Global_Named
	{

		/*Private Data*/

	public:

		Solid_Entity()
		{}

		Solid_Entity(const Standard_Integer theIndex)
			: Global_Indexed(theIndex)
		{}

		Solid_Entity
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
		{}

		virtual ~Solid_Entity()
		{}
	};
}

#endif // !_Solid_Entity_Header
