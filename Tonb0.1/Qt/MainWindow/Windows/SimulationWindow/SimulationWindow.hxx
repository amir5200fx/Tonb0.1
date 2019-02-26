#pragma once
#ifndef _SimulationWindow_Header
#define _SimulationWindow_Header

#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qmenu.h>

class QTreeWidget;
class QTreeWidgetItem;
class QPoint;

namespace AutLib
{
	class TonbTreeWidgetItem;

	class SimulationWindow
		: public QMainWindow
	{
		Q_OBJECT

	private:

		QTreeWidget* theTree_ = NULL;

	public:

		SimulationWindow(QMainWindow* parent = 0);

	private slots:

		void onCustomContextMenuRequested(const QPoint& pos);

		void showContextMenu(TonbTreeWidgetItem* item, const QPoint& globalPos);
	};
}

#endif // !_SimulationWindow_Header
