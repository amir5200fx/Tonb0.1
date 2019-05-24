#include <TonbSimulationTreeWidget.hxx>
#include <TonbGeometryTWI.hxx>
#include <TonbScenesTWI.hxx>
#include <TonbTWI.hxx>
#include <QtWidgets/qheaderview.h>
#include <QtWidgets/qtreeview.h>
#include <MainWindow.hxx>
#include <QtWidgets/qdockwidget.h>
#include <qttreepropertybrowser.h>
#include <SimulationWindow.hxx>
#include <iostream>

AutLib::TonbSimulationTreeWidget::TonbSimulationTreeWidget(SimulationWindow* parentwindow)
	: QTreeWidget((QWidget*)parentwindow)
{
	this->setColumnCount(1);
	this->setHeaderLabel(tr("Simulation"));
	this->header()->setSectionResizeMode(0, QHeaderView::Stretch);

	theGeometryItem_ = std::make_shared<TonbGeometryTWI>(parentwindow, this, tr("Geometry"));

	theScenesItem_ = std::make_shared<TonbScenesTWI>(parentwindow, this, tr("Scenes"));

	//theScenesItem_->setHidden(true);

	this->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(this,
		SIGNAL(customContextMenuRequested(const QPoint&)),
		SLOT(onCustomContextMenuRequested(const QPoint&)));

	connect(this, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(UpdatePropertySlot(QTreeWidgetItem *, int)));

	QString style = "QTreeView::branch:has-siblings:!adjoins-item {"
		"border-image:url(:/Icons/TreeStyle/stylesheet-vline.png)0;"
		"}"

		"QTreeView::branch:has-siblings:adjoins-item {"
		"    border-image: url(:/Icons/TreeStyle/stylesheet-branch-more.png) 0;"
		"}"

		"QTreeView::branch:!has-children:!has-siblings:adjoins-item {"
		"    border-image: url(:/Icons/TreeStyle/stylesheet-branch-end.png) 0;"
		"}"

		"QTreeView::branch:has-children:!has-siblings:closed,"
		"QTreeView::branch:closed:has-children:has-siblings {"
		"        border-image: none;"
		"        image: url(:/Icons/TreeStyle/User-Interface-Plus-icon.png);"
		"}"

		"QTreeView::branch:open:has-children:!has-siblings,"
		"QTreeView::branch:open:has-children:has-siblings  {"
		"        border-image: none;"
		"        image: url(:/Icons/TreeStyle/User-Interface-Minus-icon.png);"
		"}";

	this->setStyleSheet(style);
}

void AutLib::TonbSimulationTreeWidget::onCustomContextMenuRequested(const QPoint& pos)
{
	TonbTWI* item = (AutLib::TonbTWI*) this->itemAt(pos);

	if (item)
	{
		emit itemClicked(item, 0);

		showContextMenu(item, this->viewport()->mapToGlobal(pos));
	}
}

void AutLib::TonbSimulationTreeWidget::showContextMenu(TonbTWI* item, const QPoint& globalPos)
{
	item->GetContextMenu()->exec(globalPos);
}

void AutLib::TonbSimulationTreeWidget::UpdatePropertySlot(QTreeWidgetItem * item, int column)
{
	((SimulationWindow*)this->parent())->GetParentWindow()->GetPropertyDock()->setWidget(((TonbTWI*)item)->GetProperty().get());
}