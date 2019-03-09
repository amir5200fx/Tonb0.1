#include <TonbPartTreeWidgetItem.hxx>
#include <TonbSimulationTreeWidget.hxx>
#include <TonbScenesTreeWidgetItem.hxx>

AutLib::TonbPartTreeWidgetItem::TonbPartTreeWidgetItem(SimulationWindow * parentwindow, TonbTreeWidgetItem * parent, const QString & title)
	: TonbTreeWidgetItem(parentwindow, parent, title)
{
	setIcon(0, QIcon(":/Images/Icons/Part/Part_Icon.png"));
	setFlags(flags() | Qt::ItemIsEditable);

	theContextMenu_ = new PartContextMenu;

	theContextMenu_->theRenameAction_ = new QAction("Rename", (QWidget*)this->GetParentWindow());
	theContextMenu_->theNewGeometryScene_ = new QAction("New Geometry Scene", (QWidget*)this->GetParentWindow());

	GetContextMenu()->addAction(theContextMenu_->theRenameAction_);
	GetContextMenu()->addAction(theContextMenu_->theNewGeometryScene_);

	QObject::connect(theContextMenu_->theRenameAction_, SIGNAL(triggered()), this, SLOT(RenameItemSlot()));
	QObject::connect(theContextMenu_->theNewGeometryScene_, SIGNAL(triggered()), this, SLOT(AddGeometrySceneSlot()));
}



AutLib::TonbPartTreeWidgetItem::TonbPartTreeWidgetItem(const TonbPartTreeWidgetItem & part)
	: TonbTreeWidgetItem(part.GetParentWindow(), part.GetParentItem(), part.text(0))
{
	setIcon(0, QIcon(":/Images/Icons/Part/Part_Icon.png"));
}

void AutLib::TonbPartTreeWidgetItem::RenameItemSlot()
{
	GetParentView()->editItem(this);
}

void AutLib::TonbPartTreeWidgetItem::AddGeometrySceneSlot()
{
	this->GetParentView()->GetScenesItem()->AddScene(this);
}