#include <TonbVesselsTreeWidgetItem.hxx>
#include <TonbDisplacementTreeWidgetItem.hxx>
#include <QtWidgets/qmainwindow.h>
#include <Vessel_NewWindow.hxx>
#include <QtWidgets/qmenu.h>
#include <iostream>

AutLib::TonbVesselsTreeWidgetItem::TonbVesselsTreeWidgetItem(QWidget* parentwindow, TonbTreeWidgetItem * parent, const QString & title)
	: TonbTreeWidgetItem(parentwindow, parent, title)
{
	theContextMenu_ = new VesselContextMenu;

	theContextMenu_->theNewAction_ = new QAction("New", parentwindow);

	GetContextMenu()->addAction(theContextMenu_->theNewAction_);

	QObject::connect(theContextMenu_->theNewAction_, SIGNAL(triggered()), this, SLOT(CreateNewVesselWindow()));
}

void AutLib::TonbVesselsTreeWidgetItem::CreateNewVesselWindow()
{
	theNewWindow_ = new Vessel_NewWindow(this->GetParentWindow(), this);
}

void AutLib::TonbVesselsTreeWidgetItem::DeleteNewWindow(int result)
{
	if (theNewWindow_)
	{
		theNewWindow_ = NULL;
	}

	if (result)
	{
		theDisplacementItem_ = new TonbDisplacementTreeWidgetItem(this->GetParentWindow(), this, QMainWindow::tr("Displacement"));
		this->setExpanded(true);
		this->setSelected(false);
		theDisplacementItem_->setSelected(true);
		theDisplacementItem_->setIcon(0, QIcon(":/Images/Icons/Displacement_Icon.png"));
	}
}