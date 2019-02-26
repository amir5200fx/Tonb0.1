#pragma once
#ifndef _TonbVesselsTreeWidgetItem_Header
#define _TonbVesselsTreeWidgetItem_Header

#include <TonbTreeWidgetItem.hxx>

namespace AutLib
{

	class TonbDisplacementTreeWidgetItem;
	class Vessel_NewWindow;

	class TonbVesselsTreeWidgetItem
		: public TonbTreeWidgetItem
	{

	private:

		TonbDisplacementTreeWidgetItem* theNavalItem_ = NULL;

		QAction* theNewAction_ = NULL;

		Vessel_NewWindow* theNewWindow_ = NULL;

	public:

		TonbVesselsTreeWidgetItem(TonbTreeWidgetItem* parent = 0, const QString& title = "");
	};
}

#endif // !_TonbVesselsTreeWidgetItem_Header
