#include <TonbSimulationTreeWidget.hxx>
#include <TonbGeometryTreeWidgetItem.hxx>
#include <TonbTreeWidgetItem.hxx>
#include <QtWidgets/qheaderview.h>
#include <QtWidgets/qtreeview.h>
#include <iostream>

AutLib::TonbSimulationTreeWidget::TonbSimulationTreeWidget(SimulationWindow * parentwindow)
	: QTreeWidget((QWidget*)parentwindow)
{
	this->setColumnCount(1);
	this->setHeaderLabel(tr("Simulation"));
	this->header()->setSectionResizeMode(0, QHeaderView::Stretch);

	theGeometryItem_ = new TonbGeometryTreeWidgetItem(parentwindow, this, tr("Geometry"));

	this->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(this,
		SIGNAL(customContextMenuRequested(const QPoint&)),
		SLOT(onCustomContextMenuRequested(const QPoint&)));
}

void AutLib::TonbSimulationTreeWidget::onCustomContextMenuRequested(const QPoint& pos)
{
	TonbTreeWidgetItem* item = (AutLib::TonbTreeWidgetItem*) this->itemAt(pos);

	if (item)
		showContextMenu(item, this->viewport()->mapToGlobal(pos));
}

void AutLib::TonbSimulationTreeWidget::showContextMenu(TonbTreeWidgetItem* item, const QPoint& globalPos)
{
	item->GetContextMenu()->exec(globalPos);
}