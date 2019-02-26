#pragma once
#ifndef _TonbTreeWidgetItem_Header
#define _TonbTreeWidgetItem_Header

#include <QtWidgets/qtreewidget.h>

namespace AutLib
{

	class TonbTreeWidgetItem
		: public QTreeWidgetItem
	{

		QMenu* theMenu_ = NULL;

	public:

		TonbTreeWidgetItem(QTreeWidget* parent = 0, const QString& title = "");

		TonbTreeWidgetItem(TonbTreeWidgetItem* parent = 0, const QString& title = "");

		QMenu* GetContextMenu() const
		{
			return theMenu_;
		}

		QMenu*& GetContextMenu()
		{
			return theMenu_;
		}
	};
}

#endif // !_TonbTreeWidgetItem_Header
