#pragma once
#ifndef _Global_UnitSys_Header
#define _Global_UnitSys_Header

#include <UnitSystem.hxx>

namespace AutLib
{

	class Global_UnitSys
	{

		/*Private Data*/

		UnitSystem theUnit_;

	public:

		Global_UnitSys()
		{}

		Global_UnitSys(const UnitSystem theUnit)
			: theUnit_(theUnit)
		{}

		void SetImperial()
		{
			theUnit_ = UnitSystem_Imperial;
		}

		void SetSI()
		{
			theUnit_ = UnitSystem_SI;
		}

		void SetUnitSys(const UnitSystem theUnit)
		{
			theUnit_ = theUnit;
		}

		UnitSystem UnitSys() const
		{
			return theUnit_;
		}

		UnitSystem& UnitSys()
		{
			return theUnit_;
		}
	};
}

#endif // !_Global_UnitSys_Header
