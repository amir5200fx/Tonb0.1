#include <SimulationWindow.hxx>
#include <QtWidgets/qtreewidget.h>
#include <QtWidgets/qtreeview.h>
#include <QtWidgets/qheaderview.h>
#include <TonbTreeWidgetItem.hxx>
#include <QtWidgets/qdockwidget.h>
#include <TonbGeometryTreeWidgetItem.hxx>

AutLib::SimulationWindow::SimulationWindow(QMainWindow * parent)
	: QMainWindow(parent)
{
	theTree_ = new QTreeWidget(this);
	theTree_->setColumnCount(1);
	theTree_->setHeaderLabel(tr("Simulation"));
	theTree_->header()->setSectionResizeMode(0, QHeaderView::Stretch);

	AutLib::TonbGeometryTreeWidgetItem* GeometryItem = new TonbGeometryTreeWidgetItem(theTree_, tr("Geometry"));
	/*AutLib::TonbTreeWidgetItem* Geometry_CadModelItem = GeometryItem->addItemChild(tr("CAD Model"));
	AutLib::TonbTreeWidgetItem* Geometry_PartsItem = GeometryItem->addItemChild(tr("Parts"));
	AutLib::TonbTreeWidgetItem* Geometry_OperationsItem = GeometryItem->addItemChild(tr("Operations"));

	AutLib::TonbTreeWidgetItem* Geometry_ParametricItem = GeometryItem->addItemChild("Parametric Models");
	AutLib::TonbTreeWidgetItem* Geometry_Parametric_VesselItem = Geometry_ParametricItem->addItemChild("Vessels");
	AutLib::TonbTreeWidgetItem* Geometry_Parametric_ComponentsItem = Geometry_ParametricItem->addItemChild("Components");

	AutLib::TonbTreeWidgetItem* Geometry_Parametric_Vessel_DisplacementItem = Geometry_Parametric_VesselItem->addItemChild("Displacements");
	AutLib::TonbTreeWidgetItem* Geometry_Parametric_Vessel_PlanningItem = Geometry_Parametric_VesselItem->addItemChild("Plannings");

	AutLib::TonbTreeWidgetItem* Geometry_Parametric_Components_PropellerItem = Geometry_Parametric_ComponentsItem->addItemChild("Propeller");
	AutLib::TonbTreeWidgetItem* Geometry_Parametric_Components_DuctItem = Geometry_Parametric_ComponentsItem->addItemChild("Duct");
	AutLib::TonbTreeWidgetItem* Geometry_Parametric_Components_RudderItem = Geometry_Parametric_ComponentsItem->addItemChild("Rudder");
	AutLib::TonbTreeWidgetItem* Geometry_Parametric_Components_BulbousItem = Geometry_Parametric_ComponentsItem->addItemChild("Bulbous");*/

	theTree_->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(theTree_,
		SIGNAL(customContextMenuRequested(const QPoint&)),
		SLOT(onCustomContextMenuRequested(const QPoint&)));

	TonbTreeWidgetItem* ContinumItem = new TonbTreeWidgetItem(theTree_, tr("Continum"));
	TonbTreeWidgetItem* SolutionItem = new TonbTreeWidgetItem(theTree_, tr("Solution"));
	TonbTreeWidgetItem* SolutionViewsItem = new TonbTreeWidgetItem(theTree_, tr("Solution Views"));
	TonbTreeWidgetItem* PlotsItem = new TonbTreeWidgetItem(theTree_, tr("Plots"));

	this->setCentralWidget(theTree_);
}

void AutLib::SimulationWindow::onCustomContextMenuRequested(const QPoint& pos)
{
	TonbTreeWidgetItem* item = (AutLib::TonbTreeWidgetItem*) theTree_->itemAt(pos);

	if (item)
		showContextMenu(item, theTree_->viewport()->mapToGlobal(pos));
}

void AutLib::SimulationWindow::showContextMenu(TonbTreeWidgetItem* item, const QPoint& globalPos)
{
	item->GetContextMenu()->exec(globalPos);
}