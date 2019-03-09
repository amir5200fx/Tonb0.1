#pragma once
#ifndef _TonbGeometryTreeWidgetItem_Header
#define _TonbGeometryTreeWidgetItem_Header

#include <TonbTreeWidgetItem.hxx>

class QTreeWidget;

namespace AutLib
{

	class TonbParametricModelsTreeWidgetItem;
	class TonbPartsTreeWidgetItem;
	class SimulationWindow;

	class TonbGeometryTreeWidgetItem
		: public TonbTreeWidgetItem
	{

		TonbParametricModelsTreeWidgetItem* theParametricModelsItem_ = NULL;

		TonbPartsTreeWidgetItem* thePartsItem_ = NULL;

	public:

		TonbGeometryTreeWidgetItem(SimulationWindow* windowparent = 0, TonbSimulationTreeWidget* parent = 0, const QString& title = "");

		TonbParametricModelsTreeWidgetItem* GetParametricModelsTreeWidgetItem() const
		{
			return theParametricModelsItem_;
		}

		TonbParametricModelsTreeWidgetItem*& GetParametricModelsTreeWidgetItem()
		{
			return theParametricModelsItem_;
		}

		TonbPartsTreeWidgetItem* GetPartsItem() const
		{
			return thePartsItem_;
		}

		TonbPartsTreeWidgetItem*& GetPartsItem()
		{
			return thePartsItem_;
		}
	};
}

#endif // !_TonbGeometryTreeWidgetItem_Header
