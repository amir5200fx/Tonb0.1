#include <TonbVesselsTreeWidgetItem.hxx>
#include <TonbDisplacementTreeWidgetItem.hxx>
#include <QtWidgets/qmainwindow.h>
#include <Vessel_NewWindow.hxx>
#include <QtWidgets/qmenu.h>
#include<QtWidgets/qcheckbox.h>
#include <iostream>

AutLib::TonbVesselsTreeWidgetItem::TonbVesselsTreeWidgetItem(SimulationWindow* parentwindow, TonbTreeWidgetItem * parent, const QString & title)
	: TonbTreeWidgetItem(parentwindow, parent, title)
{
	theContextMenu_ = new VesselContextMenu;

	theContextMenu_->theNewAction_ = new QAction("New", (QWidget*)parentwindow);

	GetContextMenu()->addAction(theContextMenu_->theNewAction_);

	QObject::connect(theContextMenu_->theNewAction_, SIGNAL(triggered()), this, SLOT(CreateNewVesselWindow()));
}

void AutLib::TonbVesselsTreeWidgetItem::CreateNewVesselWindow()
{
	theNewWindow_ = new Vessel_NewWindow(this->GetParentWindow(), this);
}

void AutLib::TonbVesselsTreeWidgetItem::DeleteNewWindow(int result, Page2Elements* page)
{
	if (theNewWindow_)
	{
		theNewWindow_ = NULL;
	}

	if (result)
	{
		theDisplacementItems_.push_back(new TonbDisplacementTreeWidgetItem(this->GetParentWindow(), this, "Displacement " + QString::number(theDisplacementItems_.size() + 1)));
		theDisplacementItems_.at(theDisplacementItems_.size()-1)->CreateHull(page->theSymmetryCheck_->isChecked());
		this->setExpanded(true);
		this->setSelected(false);
		theDisplacementItems_.at(theDisplacementItems_.size() - 1)->setSelected(true);
		theDisplacementItems_.at(theDisplacementItems_.size() - 1)->setIcon(0, QIcon(":/Images/Icons/Displacement_Icon.png"));
	}
}

AutLib::TonbDisplacementTreeWidgetItem * AutLib::TonbVesselsTreeWidgetItem::GetDisplacement(const QString & dispName) const
{
	for (int i = 0; i < theDisplacementItems_.size(); i++)
	{
		if (dispName == theDisplacementItems_.at(i)->text(0))
			return theDisplacementItems_.at(i);
	}
}