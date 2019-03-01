#include <Vessel_NewWindow.hxx>
#include <TonbVesselsTreeWidgetItem.hxx>
#include <QtWidgets/qgroupbox.h>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qradiobutton.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qaction.h>
#include <QtGui/qpixmap.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qabstractbutton.h>
#include <iostream>

AutLib::Vessel_NewWindow::Vessel_NewWindow(QWidget * parentwindow, TonbVesselsTreeWidgetItem * parent)
	: QWizard(parentwindow,Qt::WindowCloseButtonHint)
{
	this->setPage(0, CreatePage1());
	this->setPage(1, CreatePage2());

	this->setWindowTitle(tr("New Vessel"));
	this->setWindowModality(Qt::WindowModality::WindowModal);

	this->setOption(NoBackButtonOnStartPage);

	theParentItem_ = parent;

	connect(this, SIGNAL(finished(int)), this, SLOT(CloseWindowSlot(int)));

	connect(this, SIGNAL(currentIdChanged(int)), this->button(BackButton), SLOT(show()));

	this->show();

	emit currentIdChanged(this->currentId());
}

QWizardPage* AutLib::Vessel_NewWindow::CreatePage1()
{
	QWizardPage* page1 = new QWizardPage(this);
	page1->setTitle(tr("Select Vessel Type"));

	thePage1Elements_ = new Page1Elements;

	thePage1Elements_->theRadioBtn1_ = new QRadioButton("Displacement", this);
	thePage1Elements_->theRadioBtn1_->setObjectName("Displacement");
	thePage1Elements_->theRadioBtn1_->setChecked(true);

	thePage1Elements_->theRadioBtn2_ = new QRadioButton("Semi-Displacement", this);
	thePage1Elements_->theRadioBtn2_->setObjectName("Semi-Displacement");

	thePage1Elements_->theRadioBtn3_ = new QRadioButton("Planning", this);
	thePage1Elements_->theRadioBtn3_->setObjectName("Planning");

	thePage1Elements_->theLayout_Group_ = new QVBoxLayout(this);
	thePage1Elements_->theLayout_Group_->addWidget(thePage1Elements_->theRadioBtn1_, 1);
	thePage1Elements_->theLayout_Group_->addWidget(thePage1Elements_->theRadioBtn2_, 1);
	thePage1Elements_->theLayout_Group_->addWidget(thePage1Elements_->theRadioBtn3_, 1);

	thePage1Elements_->the_GroupBox_ = new QGroupBox(this);
	thePage1Elements_->the_GroupBox_->setLayout(thePage1Elements_->theLayout_Group_);

	thePage1Elements_->theContainerLayout_ = new QHBoxLayout(this);
	thePage1Elements_->theContainerLayout_->addWidget(thePage1Elements_->the_GroupBox_);

	thePage1Elements_->theImage_ = new QLabel;
	thePage1Elements_->theImage_->setFixedSize(400, 200);

	thePage1Elements_->theContainerLayout_->addWidget(thePage1Elements_->theImage_);
	thePage1Elements_->theContainerLayout_->addStretch(1);

	page1->setLayout(thePage1Elements_->theContainerLayout_);

	connect(thePage1Elements_->theRadioBtn1_, SIGNAL(clicked()), this, SLOT(UpdateRadioBtnPage1()));
	connect(thePage1Elements_->theRadioBtn2_, SIGNAL(clicked()), this, SLOT(UpdateRadioBtnPage1()));
	connect(thePage1Elements_->theRadioBtn3_, SIGNAL(clicked()), this, SLOT(UpdateRadioBtnPage1()));

	emit thePage1Elements_->theRadioBtn1_->clicked();

	return page1;
}

QWizardPage* AutLib::Vessel_NewWindow::CreatePage2()
{
	QWizardPage* page2 = new QWizardPage(this);
	page2->setTitle(tr("Select Your Model"));

	QVBoxLayout *layout = new QVBoxLayout;
	page2->setLayout(layout);

	return page2;
}

void AutLib::Vessel_NewWindow::ShowNewWindow()
{
	this->show();
}

void AutLib::Vessel_NewWindow::UpdateRadioBtnPage1()
{
	if (thePage1Elements_->theRadioBtn1_->isChecked())
	{
		QPixmap pm(":/Images/Icons/Displacement.png");
		thePage1Elements_->theImage_->setPixmap(pm);
		thePage1Elements_->theImage_->setScaledContents(true);
	}
	else if (thePage1Elements_->theRadioBtn2_->isChecked())
	{
		QPixmap pm(":/Images/Icons/SemiDisplacement.jpg");
		thePage1Elements_->theImage_->setPixmap(pm);
		thePage1Elements_->theImage_->setScaledContents(true);
	}
	else if (thePage1Elements_->theRadioBtn3_->isChecked())
	{
		QPixmap pm(":/Images/Icons/Planning.jpg");
		thePage1Elements_->theImage_->setPixmap(pm);
		thePage1Elements_->theImage_->setScaledContents(true);
	}
}

void AutLib::Vessel_NewWindow::CloseWindowSlot(int result)
{
	this->deleteLater();

	theParentItem_->DeleteNewWindow(result);
}