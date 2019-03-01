#include <NewSimulationWindow.hxx>
#include <QtWidgets/qgroupbox.h>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qradiobutton.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qspinbox.h>
#include <QtWidgets/qpushbutton.h>
#include <QtGui/QKeyEvent>
#include <MainWindow.hxx>
#include <iostream>

AutLib::NewSimulationWindow::NewSimulationWindow(QMainWindow* parent)
	: QMainWindow(parent)
{
	this->setFixedSize(QSize(450, 600));
	this->setWindowModality(Qt::WindowModality::WindowModal);
	this->setWindowTitle(QMainWindow::tr("Create a New Simulation"));

	CreateNewWindow();

	this->theBtnOK_->setAutoDefault(true);
	this->theBtnOK_->setFocus();

	connect(this, SIGNAL(BtnOKisClickedSignal(int)), parent, SLOT(NewSimulationWindowClosedSlot(int)));
	connect(this->theBtnOK_, SIGNAL(clicked()), this, SLOT(BtnOKisClicked()));
}

AutLib::NewSimulationWindow::~NewSimulationWindow()
{
	if (theRadioBtn1_)
	{
		delete theRadioBtn1_;
		theRadioBtn1_ = NULL;
	}

	if (theRadioBtn2_)
	{
		delete theRadioBtn2_;
		theRadioBtn2_ = NULL;
	}

	if (theParallelLabel_)
	{
		delete theParallelLabel_;
		theParallelLabel_ = NULL;
	}

	if (theParallelSpin_)
	{
		delete theParallelSpin_;
		theParallelSpin_ = NULL;
	}

	if (theParallelLayout_)
	{
		delete theParallelLayout_;
		theParallelLayout_ = NULL;
	}

	if (theLayout_MPI_Group_)
	{
		delete theLayout_MPI_Group_;
		theLayout_MPI_Group_ = NULL;
	}

	if (theMPI_GroupBox_)
	{
		delete theMPI_GroupBox_;
		theMPI_GroupBox_ = NULL;
	}

	if (theBtnOK_)
	{
		delete theBtnOK_;
		theBtnOK_ = NULL;
	}

	if (theBtnCancel_)
	{
		delete theBtnCancel_;
		theBtnCancel_ = NULL;
	}


	if (theBtnLayout_)
	{
		delete theBtnLayout_;
		theBtnLayout_ = NULL;
	}


	if (the_Layout_NewSim_)
	{
		delete the_Layout_NewSim_;
		the_Layout_NewSim_ = NULL;
	}

}

void AutLib::NewSimulationWindow::CreateNewWindow()
{
	theMPI_GroupBox_ = new QGroupBox(QMainWindow::tr("Process Options"), this);
	the_Layout_NewSim_ = new QVBoxLayout;
	theLayout_MPI_Group_ = new QVBoxLayout;

	theRadioBtn1_ = new QRadioButton(QMainWindow::tr("Serial"), this);
	theRadioBtn1_->setChecked(true);

	theRadioBtn2_ = new QRadioButton(QMainWindow::tr("Parallel"), this);

	theLayout_MPI_Group_->addWidget(theRadioBtn1_);
	theLayout_MPI_Group_->addWidget(theRadioBtn2_);

	theParallelLabel_ = new QLabel(QMainWindow::tr("Compute Processes:"), this);
	theParallelSpin_ = new QSpinBox(this);
	theParallelSpin_->setValue(2);
	theParallelLayout_ = new QHBoxLayout(this);
	theParallelLayout_->addWidget(theParallelLabel_);
	theParallelLayout_->addWidget(theParallelSpin_);
	theLayout_MPI_Group_->addLayout(theParallelLayout_);
	theParallelLabel_->setVisible(false);
	theParallelSpin_->setVisible(false);

	theMPI_GroupBox_->setLayout(theLayout_MPI_Group_);

	the_Layout_NewSim_->addSpacing(10);
	the_Layout_NewSim_->addWidget(theMPI_GroupBox_);
	the_Layout_NewSim_->addStretch(1);

	theBtnOK_ = new QPushButton(QMainWindow::tr("OK"), this);
	theBtnCancel_ = new QPushButton(QMainWindow::tr("Cancel"), this);
	theBtnLayout_ = new QHBoxLayout(this);
	theBtnLayout_->addStretch(1);
	theBtnLayout_->addWidget(theBtnOK_);
	theBtnLayout_->addWidget(theBtnCancel_);

	the_Layout_NewSim_->addLayout(theBtnLayout_);

	connect(theParallelSpin_, SIGNAL(editingFinished()), this, SLOT(ShowParallelOptions()));

	connect(theRadioBtn1_, SIGNAL(clicked()), this, SLOT(ShowParallelOptions()));
	connect(theRadioBtn2_, SIGNAL(clicked()), this, SLOT(ShowParallelOptions()));

	connect(theBtnCancel_, SIGNAL(clicked()), this, SLOT(BtnCancelisClicked()));

	this->setCentralWidget(new QWidget);
	this->centralWidget()->setLayout(the_Layout_NewSim_);
	this->show();
}

void AutLib::NewSimulationWindow::ShowParallelOptions()
{
	bool b = theRadioBtn2_->isChecked();
	this->theParallelLabel_->setVisible(b);
	this->theParallelSpin_->setVisible(b);
	this->theBtnOK_->setFocus();
}

void AutLib::NewSimulationWindow::BtnOKisClicked()
{
	this->close();
	emit BtnOKisClickedSignal(1);
}

void AutLib::NewSimulationWindow::BtnCancelisClicked()
{
	this->close();
	emit BtnOKisClickedSignal(0);
}

void AutLib::NewSimulationWindow::keyPressEvent(QKeyEvent * event)
{
	if (event->key() == Qt::Key_Escape)
	{
		this->close();
		emit BtnOKisClickedSignal(0);
	}
}