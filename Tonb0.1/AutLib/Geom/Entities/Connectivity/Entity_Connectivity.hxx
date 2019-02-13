#pragma once
#ifndef _Entity_Connectivity_Header
#define _Entity_Connectivity_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{

	template<int Dim>
	class Entity_Connectivity
	{

		/*Private Data*/

		Standard_Integer theV_[Dim];

	public:

		static const Standard_Integer nbCmpts = Dim;

		Entity_Connectivity()
		{}

		Standard_Integer Value
		(
			const Standard_Integer theIndex
		) const
		{
			return theV_[theIndex];
		}

		Standard_Integer& Value
		(
			const Standard_Integer theIndex
		)
		{
			return theV_[theIndex];
		}
	};

	namespace connectivity
	{

		typedef Entity_Connectivity<2> dual;
		typedef Entity_Connectivity<3> triple;
		typedef Entity_Connectivity<4> quadruple;
		typedef Entity_Connectivity<5> quintuple;
		typedef Entity_Connectivity<6> sextuple;
		typedef Entity_Connectivity<7> septuple;
		typedef Entity_Connectivity<8> octuple;
	}
}

#endif // !_Entity_Connectivity_Header
