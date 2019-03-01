#include <SimulationWindow.hxx>
#include <TonbSimulationTreeWidget.hxx>
#include <TonbTreeWidgetItem.hxx>
#include <QtWidgets/qdockwidget.h>

AutLib::SimulationWindow::SimulationWindow(QMainWindow * parent)
	: QMainWindow(parent)
{
	theTree_ = new TonbSimulationTreeWidget(this);
	connect((QTreeWidget*)theTree_, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(ItemDoubleClickedSlot(QTreeWidgetItem*, int)));
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


	/*TonbTreeWidgetItem* ContinumItem = new TonbTreeWidgetItem(this, theTree_, tr("Continum"));
	TonbTreeWidgetItem* SolutionItem = new TonbTreeWidgetItem(this, theTree_, tr("Solution"));
	TonbTreeWidgetItem* SolutionViewsItem = new TonbTreeWidgetItem(this, theTree_, tr("Solution Views"));
	TonbTreeWidgetItem* PlotsItem = new TonbTreeWidgetItem(this, theTree_, tr("Plots"));*/

	this->setCentralWidget((QTreeWidget*)theTree_);
}

void AutLib::SimulationWindow::ItemDoubleClickedSlot(QTreeWidgetItem *item, int col)
{
	if (item->isExpanded())
		item->setExpanded(true);
	else
		item->setExpanded(false);
}

//void AutLib::SimulationWindow::RenameItem()
//{
//
//}