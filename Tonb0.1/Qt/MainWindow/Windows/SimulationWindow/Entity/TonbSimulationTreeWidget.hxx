#pragma once
#ifndef _TonbSimulationTreeWidget_Header
#define _TonbSimulationTreeWidget_Header

#include <QtWidgets/qtreewidget.h>
#include <QtWidgets/qmenu.h>

class QPoint;

namespace AutLib
{

	class TonbGeometryTreeWidgetItem;
	class TonbScenesTreeWidgetItem;
	class TonbTreeWidgetItem;
	class SimulationWindow;

	class TonbSimulationTreeWidget
		:public QTreeWidget
	{

		Q_OBJECT
	
	private:

		TonbGeometryTreeWidgetItem* theGeometryItem_ = NULL;

		TonbScenesTreeWidgetItem* theScenesItem_ = NULL;

	public:

		TonbSimulationTreeWidget(SimulationWindow* parentwindow = 0);

		TonbGeometryTreeWidgetItem* GetGeometryItem() const
		{
			return theGeometryItem_;
		}

		TonbGeometryTreeWidgetItem*& GetGeometryItem()
		{
			return theGeometryItem_;
		}

		TonbScenesTreeWidgetItem* GetScenesItem() const
		{
			return theScenesItem_;
		}

		TonbScenesTreeWidgetItem*& GetScenesItem()
		{
			return theScenesItem_;
		}

		void EditItem(QTreeWidgetItem* item, int col = 0)
		{
			editItem(item, col);
		}

	public slots:

		void onCustomContextMenuRequested(const QPoint& pos);

		void showContextMenu(TonbTreeWidgetItem* item, const QPoint& globalPos);
	};
}

#endif // !_TonbSimulationTreeWidget_Header
