#include <TonbGeometryTreeWidgetItem.hxx>
#include <TonbParametricModelsTreeWidgetItem.hxx>
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qmenu.h>

AutLib::TonbGeometryTreeWidgetItem::TonbGeometryTreeWidgetItem(QTreeWidget * parent, const QString & title)
	: TonbTreeWidgetItem(parent, title)
{
	theParametricModelsItem_ = new TonbParametricModelsTreeWidgetItem(this, QMainWindow::tr("Parametric Models"));
}