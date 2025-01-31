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
#include <QtWidgets/QProgressBar>
#include <TonbSimulationTreeWidget.hxx>
#include <TonbGeometryTWI.hxx>
#include <QtWidgets/QSizePolicy>
#include <qttreepropertybrowser.h>
#include <QtWidgets/qfiledialog.h>
#include <QtWidgets/qfileiconprovider.h>

#include <boost/archive/xml_oarchive.hpp>

AutLib::MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, Menu_File(this)
{
	Menu_File::Perform();
	this->menuBar()->addMenu(this->Menu());
	this->addToolBar(this->Toolbar());
	this->setWindowTitle("Untitled  -  Tonb++");
}

//void AutLib::MainWindow::NewSimulationWindowClosedSlot(int result)
//{
//	//delete theNewSimWindow_.get();
//
//	//theNewSimWindow_ = NULL;
//
//	if (result)
//	{
//		theSimulationWindow_ = std::make_shared<SimulationWindow>(this->shared_from_this());
//
//		theDockWidgets_.push_back(std::make_shared<QDockWidget>(this));
//		theDockWidgets_.at(theDockWidgets_.size() - 1)->setObjectName("Simulation Window");
//		theDockWidgets_.at(theDockWidgets_.size() - 1)->setWidget(theSimulationWindow_.get());
//		//theDockWidgets_.at(theDockWidgets_.size() - 1)->setMaximumWidth(280);
//		theDockWidgets_.at(theDockWidgets_.size() - 1)->setMaximumHeight(this->size().height() / 2);
//
//		this->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, theDockWidgets_.at(theDockWidgets_.size() - 1).get());
//
//		theDockWidgets_.push_back(std::make_shared<QDockWidget>(this));
//		theDockWidgets_.at(theDockWidgets_.size() - 1)->setObjectName("Properties Window");
//		theDockWidgets_.at(theDockWidgets_.size() - 1)->setWidget(theSimulationWindow_->GetTreeWidget()->GetGeometryItem()->GetProperty().get());
//		//theDockWidgets_.at(theDockWidgets_.size() - 1)->setMaximumHeight(this->size().height() / 2);
//
//		this->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, theDockWidgets_.at(theDockWidgets_.size() - 1).get());
//
//		/*QSizePolicy sizepolicy;
//		sizepolicy.setVerticalPolicy(QSizePolicy::Preferred);
//		for (int i = 0; i < theDockWidgets_.size(); i++)
//		{
//			theDockWidgets_[i]->setSizePolicy(sizepolicy); (theDockWidgets_[i]->width(), this->height() / theDockWidgets_.size());
//		}*/
//
//		this->setCentralWidget(new QWidget);
//
//		//theScene_ = new TonbSceneItem((SimulationWindow*) this, theSimulationWindow_->GetTreeWidget(), "Scene");
//		//this->setCentralWidget(theScene_);
//
//		/*theSlider_ = new QSlider(Qt::Horizontal, this);
//		theSlider_->setMinimum(0);
//		theSlider_->setMaximum(100);
//		theSlider_->setValue(100);
//		theSlider_->setMinimumHeight(25);*/
//
//		//connect(theSlider_, SIGNAL(valueChanged(int)), theScene_, SLOT(SetOpacitySlot(int)));
//
//		/*QDockWidget* SliderWidget = new QDockWidget(this);
//		SliderWidget->setWidget(theSlider_);
//		SliderWidget->setMinimumWidth(150);
//
//		this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, SliderWidget);*/
//	}
//}

void AutLib::MainWindow::NewSimulationSlot()
{
	std::shared_ptr<TonbNewSimDlg> newSimDlg = std::make_shared<TonbNewSimDlg>(this);

	if (newSimDlg->exec() == QDialog::Accepted)
	{
		theSimulationWindow_ = std::make_shared<SimulationWindow>(this->shared_from_this());

		theDockWidgets_.push_back(std::make_shared<QDockWidget>("Simulation Window", this));
		theDockWidgets_.at(theDockWidgets_.size() - 1)->setObjectName("Simulation Window");
		theDockWidgets_.at(theDockWidgets_.size() - 1)->setWidget(theSimulationWindow_.get());
		theDockWidgets_.at(theDockWidgets_.size() - 1)->setMaximumHeight(this->size().height() / 2);
		this->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, theDockWidgets_.at(theDockWidgets_.size() - 1).get());

		theProgressBar_ = std::make_shared<QProgressBar>(this);
		theProgressBar_->setTextVisible(false);
		theDockWidgets_.push_back(std::make_shared<QDockWidget>("Progress Bar", this));
		theDockWidgets_.at(theDockWidgets_.size() - 1)->setWidget(theProgressBar_.get());
		theDockWidgets_.at(theDockWidgets_.size() - 1)->setTitleBarWidget(new QWidget);
		this->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, theDockWidgets_.at(theDockWidgets_.size() - 1).get());

		theDockWidgets_.push_back(std::make_shared<QDockWidget>("Properties Window", this));
		theDockWidgets_.at(theDockWidgets_.size() - 1)->setObjectName("Properties Window");
		theDockWidgets_.at(theDockWidgets_.size() - 1)->setWidget(theSimulationWindow_->GetTreeWidget()->GetGeometryItem()->GetProperty().get());
		this->addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, theDockWidgets_.at(theDockWidgets_.size() - 1).get());

		this->setCentralWidget(new QWidget);

		Save()->setEnabled(true);
		SaveAs()->setEnabled(true);

		AppIsSaved_ = false;
	}

	//theNewSimWindow_ = std::make_shared<NewSimulationWindow>(this);
}

void AutLib::MainWindow::LoadSimulationSlot()
{
	std::shared_ptr<TonbLoadSimDlg> loadSimDlg = std::make_shared<TonbLoadSimDlg>(this);

	if (loadSimDlg->exec() == QDialog::Accepted)
	{
		Save()->setEnabled(true);
		SaveAs()->setEnabled(true);

		AppIsSaved_ = false;
	}
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
			delete theAppData_.get();
			theAppData_ = NULL;
		}
		theAppData_ = std::make_shared<AppData>();
		theAppData_->theAppFileName_ = new QString(fileName);

		/*std::ofstream ofs("sss.txt");
		assert(ofs.good());
		boost::archive::xml_oarchive oa(ofs);
		oa << BOOST_SERIALIZATION_NVP(*this);*/
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
			exit(1);
			//QApplication::quit();
		return 0;
	}
	else if (resBtn == QMessageBox::Discard)
		exit(1);
		//QApplication::quit();
	else
		return 0;
}