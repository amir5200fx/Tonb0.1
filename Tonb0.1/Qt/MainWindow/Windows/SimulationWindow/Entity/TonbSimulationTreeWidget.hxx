#pragma once
#ifndef _TonbSimulationTreeWidget_Header
#define _TonbSimulationTreeWidget_Header

#include <QtWidgets/qtreewidget.h>
#include <QtWidgets/qmenu.h>

class QPoint;

namespace AutLib
{

	class TonbGeometryTWI;
	class TonbScenesTWI;
	class TonbTWI;
	class SimulationWindow;

	class TonbSimulationTreeWidget
		:public QTreeWidget
		, public std::enable_shared_from_this<TonbSimulationTreeWidget>
	{

		Q_OBJECT
	
	private:

		std::shared_ptr<TonbGeometryTWI> theGeometryItem_ = NULL;

		std::shared_ptr<TonbScenesTWI> theScenesItem_ = NULL;

	public:

		TonbSimulationTreeWidget(SimulationWindow* parentwindow = 0);

		std::shared_ptr<TonbGeometryTWI> GetGeometryItem() const
		{
			return theGeometryItem_;
		}

		std::shared_ptr<TonbGeometryTWI>& GetGeometryItem()
		{
			return theGeometryItem_;
		}

		std::shared_ptr<TonbScenesTWI> GetScenesItem() const
		{
			return theScenesItem_;
		}

		std::shared_ptr<TonbScenesTWI>& GetScenesItem()
		{
			return theScenesItem_;
		}

		void EditItem(std::shared_ptr<QTreeWidgetItem> item, int col = 0)
		{
			editItem(item.get(), col);
		}

	public slots:

		void onCustomContextMenuRequested(const QPoint& pos);

		void showContextMenu(TonbTWI* item, const QPoint& globalPos);

		void UpdatePropertySlot(QTreeWidgetItem* item, int column);
	};
}

#endif // !_TonbSimulationTreeWidget_Header
