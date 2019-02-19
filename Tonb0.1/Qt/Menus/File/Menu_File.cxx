#include <Menu_File.hxx>
#include <QtWidgets/qaction.h>
#include <QtWidgets/qmenu.h>
#include <QtWidgets/qtoolbar.h>
#include <QtWidgets/qmenubar.h>

AutLib::Menu_File::Menu_File(QMainWindow* parent)
	: theParent_(parent)
{
}

void AutLib::Menu_File::createActions()
{
	theNew_ = new QAction(QMainWindow::tr("&New Simulation"), theParent_);
	//theNew_->setIcon(QIcon);
	theNew_->setShortcut(QMainWindow::tr("&Ctrl+N"));
	theNew_->setStatusTip(QMainWindow::tr("Create a new simulation file"));
	QMainWindow::connect(theNew_, SIGNAL(triggered()), theParent_, SLOT(NewSimulationf()));

	theLoad_ = new QAction(QMainWindow::tr("&Load Simulation"), theParent_);
	//theLoad_->setIcon();
	theLoad_->setShortcut(QMainWindow::tr("&Ctrl+L"));
	theLoad_->setStatusTip(QMainWindow::tr(""));
	QMainWindow::connect(theLoad_, SIGNAL(triggered()), theParent_, SLOT(LoadSimulationf()));
}

void AutLib::Menu_File::createMenu()
{
	theMenu_ = new QMenu(QMainWindow::tr("&File"), theParent_);

	theMenu_->addAction(theNew_);
	theMenu_->addAction(theLoad_);
}

void AutLib::Menu_File::createToolbar()
{
	//theToolbar_=new QToolBar()
}

void AutLib::Menu_File::Perform()
{
	createActions();
	createMenu();
	createToolbar();
}
