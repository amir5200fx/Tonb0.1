#include <Vessel_NewWindow.hxx>
#include <TonbVesselsTWI.hxx>
#include <QtWidgets/qgroupbox.h>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qradiobutton.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qaction.h>
#include <QtGui/qpixmap.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qabstractbutton.h>
#include <QtWidgets/qcheckbox.h>
#include <iostream>

AutLib::Vessel_NewWindow::Vessel_NewWindow
(
	SimulationWindow* parentwindow,
	TonbVesselsTWI* parent
)
	: QWizard((QWidget*)parentwindow,Qt::WindowCloseButtonHint)
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
	QWizardPage* page1 = new QWizardPage((QWidget*)this);
	page1->setTitle(tr("Select Vessel Type"));

	thePage1Elements_ = new Page1Elements;

	thePage1Elements_->theRadioBtn1_ = new QRadioButton("Displacement", (QWidget*)this);
	thePage1Elements_->theRadioBtn1_->setObjectName("Displacement");
	thePage1Elements_->theRadioBtn1_->setChecked(true);

	thePage1Elements_->theRadioBtn2_ = new QRadioButton("Semi-Displacement", (QWidget*)this);
	thePage1Elements_->theRadioBtn2_->setObjectName("Semi-Displacement");

	thePage1Elements_->theRadioBtn3_ = new QRadioButton("Planning", (QWidget*)this);
	thePage1Elements_->theRadioBtn3_->setObjectName("Planning");

	thePage1Elements_->theLayout_Group_ = new QVBoxLayout((QWidget*)this);
	thePage1Elements_->theLayout_Group_->addWidget(thePage1Elements_->theRadioBtn1_, 1);
	thePage1Elements_->theLayout_Group_->addWidget(thePage1Elements_->theRadioBtn2_, 1);
	thePage1Elements_->theLayout_Group_->addWidget(thePage1Elements_->theRadioBtn3_, 1);

	thePage1Elements_->the_GroupBox_ = new QGroupBox((QWidget*)this);
	thePage1Elements_->the_GroupBox_->setLayout(thePage1Elements_->theLayout_Group_);

	thePage1Elements_->theContainerLayout_ = new QHBoxLayout((QWidget*)this);
	thePage1Elements_->theContainerLayout_->addWidget(thePage1Elements_->the_GroupBox_);

	thePage1Elements_->theImage_ = new QLabel((QWidget*)this);
	thePage1Elements_->theImage_->setFixedSize(400, 200);

	thePage1Elements_->theContainerLayout_->addWidget(thePage1Elements_->theImage_);
	thePage1Elements_->theContainerLayout_->addStretch(1);

	page1->setLayout(thePage1Elements_->theContainerLayout_);

	connect(thePage1Elements_->theRadioBtn1_, SIGNAL(clicked()), this, SLOT(UpdateRadioBtnPage1()));
	connect(thePage1Elements_->theRadioBtn2_, SIGNAL(clicked()), this, SLOT(UpdateRadioBtnPage1()));
	connect(thePage1Elements_->theRadioBtn3_, SIGNAL(clicked()), this, SLOT(UpdateRadioBtnPage1()));

	emit thePage1Elements_->theRadioBtn1_->click();

	return page1;
}

QWizardPage* AutLib::Vessel_NewWindow::CreatePage2()
{
	QWizardPage* page2 = new QWizardPage((QWidget*)this);
	page2->setTitle(tr("Select Your Model"));

	thePage2Elements_ = new Page2Elements;

	thePage2Elements_->theRadioBtnModelNo1_ = new QRadioButton(tr("Model Number 1"), (QWidget*)this);
	thePage2Elements_->theRadioBtnModelNo1_->setChecked(true);
	thePage2Elements_->theRadioBtnModelNo2_ = new QRadioButton(tr("Model Number 2"), (QWidget*)this);

	thePage2Elements_->theSymmetryCheck_ = new QCheckBox(tr("Symmetry"), (QWidget*)this);

	thePage2Elements_->theContainerLayout_ = new QGridLayout((QWidget*)this);
	thePage2Elements_->theContainerLayout_->addWidget(thePage2Elements_->theRadioBtnModelNo1_, 0, 0);
	thePage2Elements_->theContainerLayout_->addWidget(thePage2Elements_->theRadioBtnModelNo2_, 1, 0);

	/*thePage2Elements_->theContainerLayout_ = new QVBoxLayout(this);
	thePage2Elements_->theContainerLayout_->addWidget(thePage2Elements_->theRadioBtnModelNo1_);
	thePage2Elements_->theContainerLayout_->addWidget(thePage2Elements_->theRadioBtnModelNo2_);
	thePage2Elements_->theContainerLayout_->addStretch(1);*/

	thePage2Elements_->theImage_ = new QLabel((QWidget*)this);
	thePage2Elements_->theImage_->setFixedSize(400, 200);

	thePage2Elements_->theContainerLayout_->addWidget(thePage2Elements_->theImage_, 0, 1, 3, 1);

	thePage2Elements_->theContainerLayout_->addWidget(thePage2Elements_->theSymmetryCheck_, 3, 2);

	/*QHBoxLayout* tmpLayout = new QHBoxLayout(this);
	tmpLayout->addStretch(1);
	tmpLayout->addWidget(thePage2Elements_->theSymmetryCheck_);
	thePage2Elements_->theContainerLayout_->addLayout(tmpLayout);*/

	//thePage2Elements_->theContainerLayout_->addWidget(thePage2Elements_->theSymmetryCheck_);

	thePage2Elements_->theContainerLayout_->setColumnStretch(0, 1);
	   
	page2->setLayout(thePage2Elements_->theContainerLayout_);

	connect(thePage2Elements_->theRadioBtnModelNo1_, SIGNAL(clicked()), this, SLOT(UpdateRadioBtnPage2()));
	connect(thePage2Elements_->theRadioBtnModelNo2_, SIGNAL(clicked()), this, SLOT(UpdateRadioBtnPage2()));
	connect(thePage2Elements_->theSymmetryCheck_, SIGNAL(toggled(bool)), this, SLOT(UpdateRadioBtnPage2()));

	emit thePage2Elements_->theRadioBtnModelNo1_->click();

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

		this->button(QWizard::NextButton)->setEnabled(true);
	}
	else if (thePage1Elements_->theRadioBtn2_->isChecked())
	{
		QPixmap pm(":/Images/Icons/SemiDisplacement.jpg");
		thePage1Elements_->theImage_->setPixmap(pm);
		thePage1Elements_->theImage_->setScaledContents(true);

		this->button(QWizard::NextButton)->setEnabled(false);
	}
	else if (thePage1Elements_->theRadioBtn3_->isChecked())
	{
		QPixmap pm(":/Images/Icons/Planning.jpg");
		thePage1Elements_->theImage_->setPixmap(pm);
		thePage1Elements_->theImage_->setScaledContents(true);

		this->button(QWizard::NextButton)->setEnabled(false);
	}
}

void AutLib::Vessel_NewWindow::UpdateRadioBtnPage2()
{
	if (thePage2Elements_->theRadioBtnModelNo1_->isChecked() && !thePage2Elements_->theSymmetryCheck_->isChecked())
	{
		QPixmap pm(":/Images/Icons/ModelNo1.jpeg");
		thePage2Elements_->theImage_->setPixmap(pm);
		thePage2Elements_->theImage_->setScaledContents(true);

		this->button(QWizard::FinishButton)->setEnabled(true);
	}
	else if (thePage2Elements_->theRadioBtnModelNo1_->isChecked() && thePage2Elements_->theSymmetryCheck_->isChecked())
	{
		QPixmap pm(":/Images/Icons/ModelNo1_Symmetry.jpeg");
		thePage2Elements_->theImage_->setPixmap(pm);
		thePage2Elements_->theImage_->setScaledContents(true);

		this->button(QWizard::FinishButton)->setEnabled(true);
	}
	else if (thePage2Elements_->theRadioBtnModelNo2_->isChecked())
	{
		QPixmap pm;
		thePage2Elements_->theImage_->setPixmap(pm);
		thePage2Elements_->theImage_->setScaledContents(true);

		this->button(QWizard::FinishButton)->setEnabled(false);
	}
}

void AutLib::Vessel_NewWindow::CloseWindowSlot(int result)
{

	theParentItem_->DeleteNewWindow(result, thePage2Elements_);
	//this->deleteLater();
}