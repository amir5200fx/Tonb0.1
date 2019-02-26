#include <TonbParametricModelsTreeWidgetItem.hxx>
#include <TonbVesselsTreeWidgetItem.hxx>
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qmenu.h>

AutLib::TonbParametricModelsTreeWidgetItem::TonbParametricModelsTreeWidgetItem(TonbTreeWidgetItem * parent, const QString & title)
	: TonbTreeWidgetItem(parent, title)
	//: TonbTreeWidgetItem(TonbTreeWidgetItem::addItemChild(parent, title))
{
	theVesselsItem_ = new TonbVesselsTreeWidgetItem(this, QMainWindow::tr("Vessels"));
	//theVesselsItem_->GetContextMenu()->addAction("New");
}