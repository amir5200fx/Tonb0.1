#include <TonbGeometryTWI.hxx>
#include <TonbParametricModelsTWI.hxx>
#include <TonbPartsTWI.hxx>
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qmenu.h>

AutLib::TonbGeometryTWI::TonbGeometryTWI
(
	SimulationWindow* parentwindow,
	TonbSimulationTreeWidget* parent,
	const QString & title
)
	: TonbTWI(parentwindow, parent, title)
{
	theParametricModelsItem_ = std::make_shared<TonbParametricModelsTWI>(parentwindow, this, QMainWindow::tr("Parametric Models"));

	thePartsItem_ = std::make_shared<TonbPartsTWI>(parentwindow, this, QMainWindow::tr("Parts"));
}