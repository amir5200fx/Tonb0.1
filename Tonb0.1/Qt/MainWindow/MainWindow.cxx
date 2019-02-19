//#include <qplugin.h>
//Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#include <MainWindow.hxx>
//#include "ui_mainwindow.h"
#include <QtWidgets/qaction.h>
#include <QtWidgets/qmenu.h>
#include <QtGui/QContextMenuEvent>
#include <QtWidgets/qmenubar.h>

AutLib::MainWindow::MainWindow(QWidget* parent)
	:QMainWindow(parent)
	,Menu_File(this)
	//,ui(new Ui::MainWindow)
{
	//ui->setupUi(this);
	//Menu_File::SetParent(this);
	Menu_File::Perform();
	menuBar()->addMenu(Menu());
	//Menu()->exec();
	//SetParent();
}

void AutLib::MainWindow::SetParent()
{
	/*New()->setParent(this);
	Load()->setParent(this);*/
}

//#ifndef QT_NO_CONTEXTMENU
//void AutLib::MainWindow::contextMenuEvent(QContextMenuEvent *event)
//{
//	Menu()->exec(event->globalPos());
//}
//#endif // QT_NO_CONTEXTMENU