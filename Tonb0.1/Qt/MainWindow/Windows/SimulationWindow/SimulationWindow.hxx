#pragma once
#ifndef _SimulationWindow_Header
#define _SimulationWindow_Header

#include <QtWidgets/qmainwindow.h>

class QTreeWidget;
class QTreeWidgetItem;

namespace AutLib
{
	class TonbTWI;
	class TonbSimulationTreeWidget;
	class MainWindow;

	class SimulationWindow
		: public QMainWindow
		, public std::enable_shared_from_this<SimulationWindow>
	{
		Q_OBJECT

	private:

		std::shared_ptr<TonbSimulationTreeWidget> theTree_ = NULL;

		std::shared_ptr<MainWindow> theParentWindow_ = NULL;

	public:

		SimulationWindow(std::shared_ptr<MainWindow> parent = 0);

		std::shared_ptr<TonbSimulationTreeWidget> GetTreeWidget() const
		{
			return theTree_;
		}

		std::shared_ptr<TonbSimulationTreeWidget>& GetTreeWidget()
		{
			return theTree_;
		}

		std::shared_ptr<MainWindow> GetParentWindow() const
		{
			return theParentWindow_;
		}

		std::shared_ptr<MainWindow>& GetParentWindow()
		{
			return theParentWindow_;
		}

	public slots:

		void ItemDoubleClickedSlot(QTreeWidgetItem*, int);
	};
}

#endif // !_SimulationWindow_Header
