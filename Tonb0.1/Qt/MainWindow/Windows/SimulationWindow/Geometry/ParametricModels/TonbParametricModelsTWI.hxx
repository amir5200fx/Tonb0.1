#pragma once
#ifndef _TonbParametricModelsTWI_Header
#define _TonbParametricModelsTWI_Hedaer

#include <TonbTWI.hxx>

namespace AutLib
{
	class TonbVesselsTWI;

	class TonbParametricModelsTWI
		: public TonbTWI
	{

	private:

		std::shared_ptr<TonbVesselsTWI> theVesselsItem_ = NULL;

	public:

		TonbParametricModelsTWI(SimulationWindow* parentwindow = 0, TonbTWI* parent = 0, const QString& title = "");

		std::shared_ptr<TonbVesselsTWI> GetVesselsTWI() const
		{
			return theVesselsItem_;
		}

		std::shared_ptr<TonbVesselsTWI>& GetVesselsTWI()
		{
			return theVesselsItem_;
		}
	};
}

#endif // !_TonbParametricModelsTWI_Header
