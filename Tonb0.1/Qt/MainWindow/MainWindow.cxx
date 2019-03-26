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
#include <QtWidgets/qfiledialog.h>
#include <QtWidgets/qfileiconprovider.h>

AutLib::MainWindow::MainWindow(QWidget* parent)
	:QMainWindow(parent)
	, Menu_File(this)
{
	Menu_File::Perform();
	this->menuBar()->addMenu(this->Menu());
	this->addToolBar(this->Toolbar());
	this->setWindowTitle("Untitled  -  Tonb++");
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
		//theDockWidgets_.at(theDockWidgets_.size() - 1)->setMaximumWidth(280);
		theDockWidgets_.at(theDockWidgets_.size() - 1)->setMaximumHeight(this->size().height() / 2);

		this->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, theDockWidgets_.at(theDockWidgets_.size() - 1));

		theDockWidgets_.push_back(new QDockWidget(this));
		theDockWidgets_.at(theDockWidgets_.size() - 1)->setObjectName("Properties Window");
		theDockWidgets_.at(theDockWidgets_.size() - 1)->setWidget(theSimulationWindow_->GetTreeWidget()->GetGeometryItem()->GetProperty());
		//theDockWidgets_.at(theDockWidgets_.size() - 1)->setMaximumHeight(this->size().height() / 2);

		this->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, theDockWidgets_.at(theDockWidgets_.size() - 1));

		/*QSizePolicy sizepolicy;
		sizepolicy.setVerticalPolicy(QSizePolicy::Preferred);
		for (int i = 0; i < theDockWidgets_.size(); i++)
		{
			theDockWidgets_[i]->setSizePolicy(sizepolicy); (theDockWidgets_[i]->width(), this->height() / theDockWidgets_.size());
		}*/

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

	Save()->setEnabled(true);
	SaveAs()->setEnabled(true);

	AppIsSaved_ = false;
}

void AutLib::MainWindow::LoadSimulationSlot()
{
	if (theLoadSimWindow_)
	{
		delete theLoadSimWindow_;
		theLoadSimWindow_ = NULL;
	}
	theLoadSimWindow_ = new LoadSimulationWindow(this);

	Save()->setEnabled(true);
	SaveAs()->setEnabled(true);

	AppIsSaved_ = false;
}

int AutLib::MainWindow::SaveSlot()
{
	if (!theAppData_)
	{
		SaveAsSlot();
		return 1;
	}
	else
	{
		AppIsSaved_ = true;
		return 1;
	}
}

void AutLib::MainWindow::SaveAsSlot()
{
	/*QFileDialog fileDialog((QWidget*)this, "Save As");

	fileDialog.setFileMode(QFileDialog::AnyFile);
	fileDialog.setNameFilter(tr("Tonb Files (*.tnb)"));
	fileDialog.setViewMode(QFileDialog::Detail);
	fileDialog.setAcceptMode(QFileDialog::AcceptSave);
	QFileIconProvider* dialogIcon = new QFileIconProvider;
	dialogIcon->icon(QFileIconProvider::Drive);
	fileDialog.setIconProvider(dialogIcon);

	QStringList fileName;
	if (fileDialog.exec())
	{
		fileName = fileDialog.selectedFiles();

		if (theAppFileName_)
		{
			delete theAppFileName_;
			theAppFileName_ = NULL;
		}
		theAppFileName_ = new QString(fileName[0]);

		this->setWindowTitle((*theAppFileName_) + "  -  Tonb++");
	}*/

	QString fileName = QFileDialog::getSaveFileName((QWidget*)this,
		tr("Save As..."), "",
		tr("Tonb Files (*.tnb)"));

	if (fileName.isEmpty())
		return;
	else
	{
		if (theAppData_)
		{
			delete theAppData_;
			theAppData_ = NULL;
		}
		theAppData_ = new AppData;
		theAppData_->theAppFileName_ = new QString(fileName);
	}

	this->setWindowTitle((*theAppData_->theAppFileName_) + "  -  Tonb++");

	AppIsSaved_ = true;
}

int AutLib::MainWindow::ExitSlot()
{
	if (AppIsSaved_)
			QApplication::quit();
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