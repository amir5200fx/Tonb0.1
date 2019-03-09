#pragma once
#ifndef _TonbParametricModelsTreeWidgetItem_Header
#define _TonbParametricModelsTreeWidgetItem_Hedaer

#include <TonbTreeWidgetItem.hxx>

namespace AutLib
{
	class TonbVesselsTreeWidgetItem;

	class TonbParametricModelsTreeWidgetItem
		: public TonbTreeWidgetItem
	{

	private:

		TonbVesselsTreeWidgetItem* theVesselsItem_ = NULL;

	public:

		TonbParametricModelsTreeWidgetItem(SimulationWindow* parentwindow = 0, TonbTreeWidgetItem* parent = 0, const QString& title = "");

		TonbVesselsTreeWidgetItem* GetVesselsTreeWidgetItem() const
		{
			return theVesselsItem_;
		}

		TonbVesselsTreeWidgetItem*& GetVesselsTreeWidgetItem()
		{
			return theVesselsItem_;
		}
	};
}

#endif // !_TonbParametricModelsTreeWidgetItem_Header
