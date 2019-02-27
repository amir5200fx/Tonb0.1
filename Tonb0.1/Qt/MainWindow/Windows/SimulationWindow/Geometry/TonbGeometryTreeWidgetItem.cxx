#include <TonbGeometryTreeWidgetItem.hxx>
#include <TonbParametricModelsTreeWidgetItem.hxx>
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qmenu.h>

AutLib::TonbGeometryTreeWidgetItem::TonbGeometryTreeWidgetItem(QWidget* parentwindow, QTreeWidget * parent, const QString & title)
	: TonbTreeWidgetItem(parentwindow, parent, title)
{
	theParametricModelsItem_ = new TonbParametricModelsTreeWidgetItem(parentwindow, this, QMainWindow::tr("Parametric Models"));
}