#include <TonbTreeWidgetItem.hxx>
#include <TonbSimulationTreeWidget.hxx>
#include <QtWidgets/qmenu.h>

AutLib::TonbTreeWidgetItem::TonbTreeWidgetItem(SimulationWindow* parentwindow, TonbSimulationTreeWidget * parent, const QString& title)
	: QTreeWidgetItem((QTreeWidget*)parent)
	, theParentView_(parent)
{
	setText(0, title);
	setIcon(0, QIcon(":/Menus/Icons/Menus/File/Load.png"));
	parent->addTopLevelItem(this);
	theMenu_ = new QMenu;

	theParentWindow_ = parentwindow;
}

AutLib::TonbTreeWidgetItem::TonbTreeWidgetItem(SimulationWindow* parentwindow, TonbTreeWidgetItem* parent, const QString& title)
	: QTreeWidgetItem(parent)
	, theParentItem_(parent)
{
	setText(0, title);
	setIcon(0, QIcon(":/Menus/Icons/Menus/File/Load.png"));
	addChild(parent);
	theMenu_ = new QMenu;

	theParentWindow_ = parentwindow;

	theParentView_ = parent->GetParentView();
}