#include <TonbParametricModelsTreeWidgetItem.hxx>
#include <TonbVesselsTreeWidgetItem.hxx>
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qmenu.h>

AutLib::TonbParametricModelsTreeWidgetItem::TonbParametricModelsTreeWidgetItem(QWidget* parentwindow, TonbTreeWidgetItem * parent, const QString & title)
	: TonbTreeWidgetItem(parentwindow, parent, title)
	//: TonbTreeWidgetItem(TonbTreeWidgetItem::addItemChild(parent, title))
{
	theVesselsItem_ = new TonbVesselsTreeWidgetItem(parentwindow, this, QMainWindow::tr("Vessels"));
	//theVesselsItem_->GetContextMenu()->addAction("New");
}