#include <TonbTreeWidgetItem.hxx>
#include <QtWidgets/qmenu.h>

AutLib::TonbTreeWidgetItem::TonbTreeWidgetItem(QWidget* parentwindow, QTreeWidget * parent, const QString& title)
	: QTreeWidgetItem(parent)
{
	setText(0, title);
	setIcon(0, QIcon(":/Menus/Icons/Menus/File/Load.png"));
	parent->addTopLevelItem(this);
	theMenu_ = new QMenu;

	theParentWindow_ = parentwindow;
}

AutLib::TonbTreeWidgetItem::TonbTreeWidgetItem(QWidget* parentwindow, TonbTreeWidgetItem* parent, const QString& title)
	: QTreeWidgetItem(parent)
{
	setText(0, title);
	setIcon(0, QIcon(":/Menus/Icons/Menus/File/Load.png"));
	addChild(parent);
	theMenu_ = new QMenu;

	theParentWindow_ = parentwindow;
}