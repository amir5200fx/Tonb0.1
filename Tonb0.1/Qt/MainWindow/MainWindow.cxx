#include <MainWindow.hxx>
#include <QtWidgets/qmenubar.h>
#include <QtWidgets/qtoolbar.h>
#include <QtWidgets/qmessagebox.h>
#include <SimulationWindow.hxx>
#include <TonbSceneItem.hxx>
#include <QtWidgets/qslider.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/QSpacerItem>
#include <TonbSimulationTreeWidget.hxx>
#include <TonbGeometryTreeWidgetItem.hxx>
#include <QtWidgets/QSizePolicy>
#include <qttreepropertybrowser.h>

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

		theDockWidgets_.push_back(new QDockWidget(this));
		theDockWidgets_.at(theDockWidgets_.size() - 1)->setObjectName("Simulation Window");
		theDockWidgets_.at(theDockWidgets_.size() - 1)->setWidget(theSimulationWindow_);
		theDockWidgets_.at(theDockWidgets_.size() - 1)->setMaximumWidth(280);
		//theDockWidgets_.at(theDockWidgets_.size() - 1)->setMaximumHeight(this->size().height() / 2);

		this->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, theDockWidgets_.at(theDockWidgets_.size() - 1));

		theDockWidgets_.push_back(new QDockWidget(this));
		theDockWidgets_.at(theDockWidgets_.size() - 1)->setObjectName("Properties Window");
		theDockWidgets_.at(theDockWidgets_.size() - 1)->setWidget(theSimulationWindow_->GetTreeWidget()->GetGeometryItem()->GetProperty());
		//theDockWidgets_.at(theDockWidgets_.size() - 1)->setMaximumHeight(this->size().height() / 2);

		this->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, theDockWidgets_.at(theDockWidgets_.size() - 1));

		QSizePolicy sizepolicy;
		sizepolicy.setVerticalPolicy(QSizePolicy::Preferred);
		for (int i = 0; i < theDockWidgets_.size(); i++)
		{
			theDockWidgets_[i]->setSizePolicy(sizepolicy); (theDockWidgets_[i]->width(), this->height() / theDockWidgets_.size());
		}

		this->setCentralWidget(new QWidget);

		//theScene_ = new TonbSceneItem((SimulationWindow*) this, theSimulationWindow_->GetTreeWidget(), "Scene");
		//this->setCentralWidget(theScene_);

		/*theSlider_ = new QSlider(Qt::Horizontal, this);
		theSlider_->setMinimum(0);
		theSlider_->setMaximum(100);
		theSlider_->setValue(100);
		theSlider_->setMinimumHeight(25);*/

		//connect(theSlider_, SIGNAL(valueChanged(int)), theScene_, SLOT(SetOpacitySlot(int)));

		/*QDockWidget* SliderWidget = new QDockWidget(this);
		SliderWidget->setWidget(theSlider_);
		SliderWidget->setMinimumWidth(150);

		this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, SliderWidget);*/
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