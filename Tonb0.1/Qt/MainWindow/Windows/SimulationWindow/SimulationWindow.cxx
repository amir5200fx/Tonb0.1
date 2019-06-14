#include <SimulationWindow.hxx>
#include <TonbSimulationTreeWidget.hxx>
#include <TonbTWI.hxx>
#include <MainWindow.hxx>
#include <QtWidgets/qdockwidget.h>

AutLib::SimulationWindow::SimulationWindow(std::shared_ptr<MainWindow> parent)
	: QMainWindow(parent.get())
{
	theTreeWidget_ = std::make_shared<TonbSimulationTreeWidget>(this);
	connect
	(
		(QTreeWidget*)theTreeWidget_.get(),
		SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)),
		this,
		SLOT(ItemDoubleClickedSlot(QTreeWidgetItem*, int))
	);
	/*AutLib::TonbTWI* Geometry_CadModelItem = GeometryItem->addItemChild(tr("CAD Model"));
	AutLib::TonbTWI* Geometry_PartsItem = GeometryItem->addItemChild(tr("Parts"));
	AutLib::TonbTWI* Geometry_OperationsItem = GeometryItem->addItemChild(tr("Operations"));

	AutLib::TonbTWI* Geometry_ParametricItem = GeometryItem->addItemChild("Parametric Models");
	AutLib::TonbTWI* Geometry_Parametric_VesselItem = Geometry_ParametricItem->addItemChild("Vessels");
	AutLib::TonbTWI* Geometry_Parametric_ComponentsItem = Geometry_ParametricItem->addItemChild("Components");

	AutLib::TonbTWI* Geometry_Parametric_Vessel_DisplacementItem = Geometry_Parametric_VesselItem->addItemChild("Displacements");
	AutLib::TonbTWI* Geometry_Parametric_Vessel_PlanningItem = Geometry_Parametric_VesselItem->addItemChild("Plannings");

	AutLib::TonbTWI* Geometry_Parametric_Components_PropellerItem = Geometry_Parametric_ComponentsItem->addItemChild("Propeller");
	AutLib::TonbTWI* Geometry_Parametric_Components_DuctItem = Geometry_Parametric_ComponentsItem->addItemChild("Duct");
	AutLib::TonbTWI* Geometry_Parametric_Components_RudderItem = Geometry_Parametric_ComponentsItem->addItemChild("Rudder");
	AutLib::TonbTWI* Geometry_Parametric_Components_BulbousItem = Geometry_Parametric_ComponentsItem->addItemChild("Bulbous");*/


	/*TonbTWI* ContinumItem = new TonbTWI(this, theTree_, tr("Continum"));
	TonbTWI* SolutionItem = new TonbTWI(this, theTree_, tr("Solution"));
	TonbTWI* SolutionViewsItem = new TonbTWI(this, theTree_, tr("Solution Views"));
	TonbTWI* PlotsItem = new TonbTWI(this, theTree_, tr("Plots"));*/

	this->setCentralWidget((QTreeWidget*)theTreeWidget_.get());

	theParentWindow_ = parent;
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