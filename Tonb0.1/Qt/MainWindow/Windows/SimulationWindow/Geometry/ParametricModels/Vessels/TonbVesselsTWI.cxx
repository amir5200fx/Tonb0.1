#include <TonbVesselsTWI.hxx>
#include <TonbDisplacementTWI.hxx>
#include <QtWidgets/qmainwindow.h>
#include <Vessel_NewWindow.hxx>
#include <QtWidgets/qmenu.h>
#include<QtWidgets/qcheckbox.h>
#include <iostream>

AutLib::TonbVesselsTWI::TonbVesselsTWI
(
	SimulationWindow* parentwindow,
	TonbTWI* parent,
	const QString & title
)
	: TonbTWI(parentwindow, parent, title)
{
	theContextMenu_ = std::make_shared<VesselContextMenu>();

	theContextMenu_->theNewAction_ = new QAction("New", (QWidget*)parentwindow);

	GetContextMenu()->addAction(theContextMenu_->theNewAction_);

	QObject::connect(theContextMenu_->theNewAction_, SIGNAL(triggered()), this, SLOT(CreateNewVesselWindow()));
}

void AutLib::TonbVesselsTWI::CreateNewVesselWindow()
{
	theNewWindow_ = std::make_shared<Vessel_NewWindow>(this->GetParentWindow(), this);
}

void AutLib::TonbVesselsTWI::DeleteNewWindow(int result, Page2Elements* page)
{
	/*if (theNewWindow_)
	{
		theNewWindow_ = NULL;
	}*/

	if (result)
	{
		theDisplacementItems_.push_back(std::make_shared<TonbDisplacementTWI>(this->GetParentWindow(), (TonbTWI*)this, TonbTWI::CorrectName((TonbTWI*)this, "Displacement")));
		theDisplacementItems_.last()->CreateHull(page->theSymmetryCheck_->isChecked());
		this->setExpanded(true);
		this->setSelected(false);
		theDisplacementItems_.at(theDisplacementItems_.size() - 1)->setSelected(true);
		theDisplacementItems_.at(theDisplacementItems_.size() - 1)->setIcon(0, QIcon(":/Images/Icons/Displacement_Icon.png"));
	}
}

std::shared_ptr<AutLib::TonbDisplacementTWI> AutLib::TonbVesselsTWI::GetDisplacement(const QString & dispName) const
{
	for (int i = 0; i < theDisplacementItems_.size(); i++)
	{
		if (dispName == theDisplacementItems_.at(i)->text(0))
			return theDisplacementItems_.at(i);
	}
}