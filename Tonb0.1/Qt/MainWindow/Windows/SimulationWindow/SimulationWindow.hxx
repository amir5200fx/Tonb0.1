#pragma once
#ifndef _SimulationWindow_Header
#define _SimulationWindow_Header

#include <QtWidgets/qmainwindow.h>

class QTreeWidget;
class QTreeWidgetItem;

namespace AutLib
{
	class TonbTreeWidgetItem;
	class TonbSimulationTreeWidget;
	class MainWindow;

	class SimulationWindow
		: public QMainWindow
	{
		Q_OBJECT

	private:

		TonbSimulationTreeWidget* theTree_ = NULL;

		MainWindow* theParentWindow_ = NULL;

	public:

		SimulationWindow(QMainWindow* parent = 0);

		TonbSimulationTreeWidget* GetTreeWidget() const
		{
			return theTree_;
		}

		TonbSimulationTreeWidget*& GetTreeWidget()
		{
			return theTree_;
		}

		MainWindow* GetParentWindow() const
		{
			return theParentWindow_;
		}

		MainWindow*& GetParentWindow()
		{
			return theParentWindow_;
		}

	public slots:

		void ItemDoubleClickedSlot(QTreeWidgetItem*, int);
	};
}

#endif // !_SimulationWindow_Header
