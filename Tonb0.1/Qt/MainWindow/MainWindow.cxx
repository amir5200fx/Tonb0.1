#include <MainWindow.hxx>
#include <QtWidgets/qmenubar.h>
#include <QtWidgets/qtoolbar.h>

AutLib::MainWindow::MainWindow(QWidget* parent)
	:QMainWindow(parent)
	,Menu_File(this)
{
	Menu_File::Perform();
	menuBar()->addMenu(Menu());
	this->addToolBar(this->Toolbar());
}

void AutLib::MainWindow::SetParent()
{
}