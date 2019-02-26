#include <Vessel_NewWindow.hxx>
#include <TonbVesselsTreeWidgetItem.hxx>
#include <QtWidgets/qgroupbox.h>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qradiobutton.h>
#include <QtWidgets/qpushbutton.h>

AutLib::Vessel_NewWindow::Vessel_NewWindow(TonbVesselsTreeWidgetItem * parent)
	: QMainWindow(0)
{
	//this->setFixedSize(QSize(120, 64));
	this->setWindowModality(Qt::WindowModality::WindowModal);
	this->setWindowTitle(QMainWindow::tr("New Vessel"));

	theRadioBtn1_ = new QRadioButton("Displacement", 0);
	theRadioBtn1_->setObjectName("Displacement");
	theRadioBtn2_ = new QRadioButton("Semi-Displacement", 0);
	theRadioBtn2_->setObjectName("Semi-Displacement");
	theRadioBtn3_ = new QRadioButton("Planning", 0);
	theRadioBtn3_->setObjectName("Planning");

	theLayout_Group_ = new QVBoxLayout(0);
	theLayout_Group_->addWidget(theRadioBtn1_, 1);
	theLayout_Group_->addWidget(theRadioBtn2_, 1);
	theLayout_Group_->addWidget(theRadioBtn3_, 1);

	the_GroupBox_ = new QGroupBox("Vessel Types",0);
	the_GroupBox_->setLayout(theLayout_Group_);
	the_Layout_ = new QVBoxLayout(0);

	the_EnabledGroupBox_ = new QGroupBox("Enabled Types", 0);

	theEnabledLayout_ = new QVBoxLayout(0);
	theEnabledLayout_->addWidget(the_EnabledGroupBox_);
	theContainerLayout_ = new QHBoxLayout(0);
	theContainerLayout_->addWidget(the_GroupBox_);
	theContainerLayout_->addLayout(theEnabledLayout_);
	the_Layout_->addLayout(theContainerLayout_);

	theBtnClose_ = new QPushButton("Close", 0);
	theBtnHelp_ = new QPushButton("Help", 0);

	theBtnLayout_ = new QHBoxLayout(0);
	theBtnLayout_->addStretch(1);
	theBtnLayout_->addWidget(theBtnClose_);
	theBtnLayout_->addWidget(theBtnHelp_);

	the_Layout_->addLayout(theBtnLayout_);
}

void AutLib::Vessel_NewWindow::ShowNewWindow()
{
	this->setCentralWidget(new QWidget);
	this->centralWidget()->setLayout(the_Layout_);
	this->show();
}