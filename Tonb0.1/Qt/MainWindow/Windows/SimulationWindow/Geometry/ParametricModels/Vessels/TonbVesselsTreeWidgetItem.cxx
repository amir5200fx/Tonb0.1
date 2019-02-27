#include <TonbVesselsTreeWidgetItem.hxx>
#include <TonbDisplacementTreeWidgetItem.hxx>
#include <QtWidgets/qmainwindow.h>
#include <Vessel_NewWindow.hxx>
#include <QtWidgets/qmenu.h>

AutLib::TonbVesselsTreeWidgetItem::TonbVesselsTreeWidgetItem(QWidget* parentwindow, TonbTreeWidgetItem * parent, const QString & title)
	: TonbTreeWidgetItem(parentwindow, parent, title)
{
	theNewAction_ = new QAction("New", 0);
	GetContextMenu()->addAction(theNewAction_);

	theNavalItem_ = new TonbDisplacementTreeWidgetItem(parentwindow, this, QMainWindow::tr("Displacement"));

	theNewWindow_ = new Vessel_NewWindow(parentwindow, this);

	QObject::connect(theNewAction_, SIGNAL(triggered()), theNewWindow_, SLOT(ShowNewWindow()));
}