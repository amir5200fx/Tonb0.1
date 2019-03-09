#include <TonbGeometryTreeWidgetItem.hxx>
#include <TonbParametricModelsTreeWidgetItem.hxx>
#include <TonbPartsTreeWidgetItem.hxx>
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qmenu.h>

AutLib::TonbGeometryTreeWidgetItem::TonbGeometryTreeWidgetItem(SimulationWindow* parentwindow, TonbSimulationTreeWidget * parent, const QString & title)
	: TonbTreeWidgetItem(parentwindow, parent, title)
{
	theParametricModelsItem_ = new TonbParametricModelsTreeWidgetItem(parentwindow, this, QMainWindow::tr("Parametric Models"));

	thePartsItem_ = new TonbPartsTreeWidgetItem(parentwindow, this, QMainWindow::tr("Parts"));
}