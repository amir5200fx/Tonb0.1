#pragma once
#ifndef _TonbTreeWidgetItem_Header
#define _TonbTreeWidgetItem_Header

#include <QtWidgets/qtreewidget.h>

class QtTreePropertyBrowser;

namespace AutLib
{

	class TonbSimulationTreeWidget;
	class SimulationWindow;

	class TonbTreeWidgetItem
		: public QTreeWidgetItem
	{

		QMenu* theMenu_ = NULL;

		SimulationWindow* theParentWindow_ = NULL;

		TonbTreeWidgetItem* theParentItem_ = NULL;

		TonbSimulationTreeWidget* theParentView_ = NULL;

		QtTreePropertyBrowser* theProperty_ = NULL;

	public:

		TonbTreeWidgetItem(SimulationWindow* parentwindow = 0, TonbSimulationTreeWidget* parent = 0, const QString& title = "");

		TonbTreeWidgetItem(SimulationWindow* parentwindow = 0, TonbTreeWidgetItem* parent = 0, const QString& title = "");

		void CreateProperty();

		QMenu* GetContextMenu() const
		{
			return theMenu_;
		}

		QMenu*& GetContextMenu()
		{
			return theMenu_;
		}

		SimulationWindow* GetParentWindow() const
		{
			return theParentWindow_;
		}

		SimulationWindow*& GetParentWindow()
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

		TonbSimulationTreeWidget* GetParentView() const
		{
			return theParentView_;
		}

		TonbSimulationTreeWidget*& GetParentView()
		{
			return theParentView_;
		}

		QtTreePropertyBrowser* GetProperty() const
		{
			return theProperty_;
		}

		QtTreePropertyBrowser*& GetProperty()
		{
			return theProperty_;
		}
	};
}

#endif // !_TonbTreeWidgetItem_Header
