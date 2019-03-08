#include <TonbDisplacementTreeWidgetItem.hxx>
#include <TonbSimulationTreeWidget.hxx>
#include <TonbGeometryTreeWidgetItem.hxx>
#include <TonbPartsTreeWidgetItem.hxx>
#include <TonbPartTreeWidgetItem.hxx>
#include <QtWidgets/qaction.h>
#include <QtWidgets/qmenu.h>
#include <Vessels_DispNo1.hxx>

AutLib::TonbDisplacementTreeWidgetItem::TonbDisplacementTreeWidgetItem(SimulationWindow* parentwindow, TonbTreeWidgetItem * parent, const QString & title)
	: TonbTreeWidgetItem(parentwindow, parent, title)
{
	setFlags(flags() | Qt::ItemIsEditable);

	CreateMenu();

	//CreateHull();
}

void AutLib::TonbDisplacementTreeWidgetItem::RenameItemSlot()
{
	GetParentView()->editItem(this);
}

void AutLib::TonbDisplacementTreeWidgetItem::CreateHull(bool Symmetry)
{
	if (Symmetry)
		theHull_ = std::make_shared<DispNo1_HullPatch>();
	else
		theHull_ = std::make_shared<DispNo1_BareHull>();

	theHull_->Perform();

	
	if (!Symmetry)
	{
		std::cout << std::dynamic_pointer_cast<DispNo1_BareHull>(theHull_)->typeName << std::endl;
	}
	else
		std::cout << theHull_->typeName << std::endl;

}

void AutLib::TonbDisplacementTreeWidgetItem::CreateMenu()
{
	theContextMenu_ = new DisplacementContextMenu;

	theContextMenu_->theRenameAction_ = new QAction("Rename", (QWidget*)this->GetParentWindow());
	GetContextMenu()->addAction(theContextMenu_->theRenameAction_);

	theContextMenu_->theNewGeometryPartAction_ = new QAction("New Geometry Part", (QWidget*)this->GetParentWindow());
	GetContextMenu()->addAction(theContextMenu_->theNewGeometryPartAction_);

	QObject::connect(theContextMenu_->theRenameAction_, SIGNAL(triggered()), this, SLOT(RenameItemSlot()));

	QObject::connect(theContextMenu_->theNewGeometryPartAction_, SIGNAL(triggered()), this, SLOT(NewGeometryPartSlot()));
}

void AutLib::TonbDisplacementTreeWidgetItem::NewGeometryPartSlot()
{
	GetParentView()->GetGeometryItem()->GetPartsItem()->AddPart(this);
}