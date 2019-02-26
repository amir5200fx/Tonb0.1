#include <TonbTreeWidgetItem.hxx>
#include <QtWidgets/qmenu.h>

AutLib::TonbTreeWidgetItem::TonbTreeWidgetItem(QTreeWidget * parent, const QString& title)
	: QTreeWidgetItem(parent)
{
	setText(0, title);
	setIcon(0, QIcon(":/Menus/Icons/Menus/File/Load.png"));
	parent->addTopLevelItem(this);
	theMenu_ = new QMenu;
}

AutLib::TonbTreeWidgetItem::TonbTreeWidgetItem(TonbTreeWidgetItem* parent, const QString& title)
	: QTreeWidgetItem(parent)
{
	setText(0, title);
	setIcon(0, QIcon(":/Menus/Icons/Menus/File/Load.png"));
	addChild(parent);
	theMenu_ = new QMenu;
}