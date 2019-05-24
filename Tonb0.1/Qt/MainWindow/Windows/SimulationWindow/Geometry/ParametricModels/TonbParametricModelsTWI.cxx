#include <TonbParametricModelsTWI.hxx>
#include <TonbVesselsTWI.hxx>
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qmenu.h>

AutLib::TonbParametricModelsTWI::TonbParametricModelsTWI
(
	SimulationWindow* parentwindow,
	TonbTWI* parent,
	const QString & title
)
	: TonbTWI(parentwindow, parent, title)
	//: TonbTWI(TonbTWI::addItemChild(parent, title))
{
	theVesselsItem_ = std::make_shared<TonbVesselsTWI>(parentwindow, this, QMainWindow::tr("Vessels"));
	//theVesselsItem_->GetContextMenu()->addAction("New");
}