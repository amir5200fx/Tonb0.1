#include <MainWindow.hxx>
#include <QtWidgets/qmenubar.h>
#include <QtWidgets/qtoolbar.h>
#include <QtWidgets/qmessagebox.h>
#include <SimulationWindow.hxx>
#include <QtWidgets/qdockwidget.h>

AutLib::MainWindow::MainWindow(QWidget* parent)
	:QMainWindow(parent)
	, Menu_File(this)
{
	Menu_File::Perform();
	this->menuBar()->addMenu(this->Menu());
	this->addToolBar(this->Toolbar());
}

void AutLib::MainWindow::NewSimulationWindowClosedSlot(int result)
{
	delete theNewSimWindow_;

	theNewSimWindow_ = NULL;

	if (result)
	{
		theSimulationWindow_ = new SimulationWindow(this);

		QDockWidget* theDock = new QDockWidget(this);
		theDock->setWidget(theSimulationWindow_);
		theDock->setMaximumWidth(300);

		this->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, theDock);
	}
}

void AutLib::MainWindow::NewSimulationSlot()
{
	if (theNewSimWindow_)
	{
		delete theNewSimWindow_;
		theNewSimWindow_ = NULL;
	}
	theNewSimWindow_ = new NewSimulationWindow(this);
}

void AutLib::MainWindow::LoadSimulationSlot()
{
	if (theLoadSimWindow_)
	{
		delete theLoadSimWindow_;
		theLoadSimWindow_ = NULL;
	}
	theLoadSimWindow_ = new LoadSimulationWindow(this);
}

int AutLib::MainWindow::ExitSlot()
{
	QMessageBox::StandardButton resBtn = QMessageBox::warning(this, "Tonb",
		tr("The simulation has been modified.\nDo you want to save your changes?"),
		QMessageBox::Cancel | QMessageBox::Discard | QMessageBox::Save,
		QMessageBox::Save);

	if (resBtn == QMessageBox::Save)
	{
		if (this->SaveSlot())
			QApplication::quit();
		return 0;
	}
	else if (resBtn == QMessageBox::Discard)
		QApplication::quit();
	else
		return 0;
}