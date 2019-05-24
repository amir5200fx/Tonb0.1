#pragma once
#ifndef _TonbGeometryTWI_Header
#define _TonbGeometryTWI_Header

#include <TonbTWI.hxx>

class QTreeWidget;

namespace AutLib
{

	class TonbParametricModelsTWI;
	class TonbPartsTWI;
	class SimulationWindow;

	class TonbGeometryTWI
		: public TonbTWI
	{

		std::shared_ptr<TonbParametricModelsTWI> theParametricModelsItem_ = NULL;

		std::shared_ptr<TonbPartsTWI> thePartsItem_ = NULL;

	public:

		TonbGeometryTWI(SimulationWindow* windowparent = 0, TonbSimulationTreeWidget* parent = 0, const QString& title = "");

		std::shared_ptr<TonbParametricModelsTWI> GetParametricModelsTWI() const
		{
			return theParametricModelsItem_;
		}

		std::shared_ptr<TonbParametricModelsTWI>& GetParametricModelsTWI()
		{
			return theParametricModelsItem_;
		}

		std::shared_ptr<TonbPartsTWI> GetPartsItem() const
		{
			return thePartsItem_;
		}

		std::shared_ptr<TonbPartsTWI>& GetPartsItem()
		{
			return thePartsItem_;
		}
	};
}

#endif // !_TonbGeometryTWI_Header
