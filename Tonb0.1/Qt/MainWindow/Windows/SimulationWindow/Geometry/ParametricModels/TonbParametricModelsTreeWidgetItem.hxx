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

		TonbParametricModelsTreeWidgetItem(TonbTreeWidgetItem* parent = 0, const QString& title = "");
	};
}

#endif // !_TonbParametricModelsTreeWidgetItem_Header
