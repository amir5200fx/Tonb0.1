#include <TonbVesselsTreeWidgetItem.hxx>
#include <QtWidgets/qmenu.h>
#include <TonbDisplacementTreeWidgetItem.hxx>
#include <QtWidgets/qmainwindow.h>
#include <QtCore/QObject>
#include <Vessel_NewWindow.hxx>

AutLib::TonbVesselsTreeWidgetItem::TonbVesselsTreeWidgetItem(TonbTreeWidgetItem * parent, const QString & title)
	: TonbTreeWidgetItem(parent, title)
{
	theNewAction_ = new QAction("New", 0);
	GetContextMenu()->addAction(theNewAction_);

	theNavalItem_ = new TonbDisplacementTreeWidgetItem(this, QMainWindow::tr("Displacement"));

	theNewWindow_ = new Vessel_NewWindow(this);

	QObject::connect(theNewAction_, SIGNAL(triggered()), theNewWindow_, SLOT(ShowNewWindow()));
}