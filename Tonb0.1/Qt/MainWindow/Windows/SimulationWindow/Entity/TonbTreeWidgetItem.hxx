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

		QWidget* theParentWindow_ = NULL;

		TonbTreeWidgetItem* theParentItem_ = NULL;

		QTreeWidget* theParentView_ = NULL;

	public:

		TonbTreeWidgetItem(QWidget* parentwindow = 0, QTreeWidget* parent = 0, const QString& title = "");

		TonbTreeWidgetItem(QWidget* parentwindow = 0, TonbTreeWidgetItem* parent = 0, const QString& title = "");

		QMenu* GetContextMenu() const
		{
			return theMenu_;
		}

		QMenu*& GetContextMenu()
		{
			return theMenu_;
		}

		QWidget* GetParentWindow() const
		{
			return theParentWindow_;
		}

		QWidget*& GetParentWindow()
		{
			return theParentWindow_;
		}

		TonbTreeWidgetItem* GetParentItem() const
		{
			return theParentItem_;
		}

		TonbTreeWidgetItem*& GetParentItem()
		{
			return theParentItem_;
		}

		QTreeWidget* GetParentView() const
		{
			return theParentView_;
		}

		QTreeWidget*& GetParentView()
		{
			return theParentView_;
		}
	};
}

#endif // !_TonbTreeWidgetItem_Header
