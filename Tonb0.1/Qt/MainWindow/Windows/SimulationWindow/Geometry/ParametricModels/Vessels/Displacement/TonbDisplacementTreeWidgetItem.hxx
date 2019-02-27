#pragma once
#ifndef _TonbDisplacementTreeWidgetItem_Header
#define _TonbDisplacementTreeWidgetItem_Header

#include <TonbTreeWidgetItem.hxx>

namespace AutLib
{

	class TonbDisplacementTreeWidgetItem
		: public TonbTreeWidgetItem
	{

	public:

		TonbDisplacementTreeWidgetItem(QWidget* parentwindow = 0, TonbTreeWidgetItem* parent = 0, const QString& title = "");
	};
}

#endif // !_TonbDisplacementTreeWidgetItem_Header
