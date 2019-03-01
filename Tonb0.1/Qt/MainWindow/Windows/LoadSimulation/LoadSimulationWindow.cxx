#include <LoadSimulationWindow.hxx>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlineedit.h>

AutLib::LoadSimulationWindow::LoadSimulationWindow(QMainWindow* parent)
	:NewSimulationWindow(parent)
{
	this->setWindowTitle(QMainWindow::tr("Load Simulation"));

	theBrowseLabel_ = new QLabel(QMainWindow::tr("File"), this);
	theBrowseBtn_ = new QPushButton(QMainWindow::tr("Browse"), this);
	theBrowseLineEdit_ = new QLineEdit(this);
	theBrowseLayout_ = new QHBoxLayout(this);
	
	theBrowseLayout_->addWidget(theBrowseLabel_);
	theBrowseLayout_->addWidget(theBrowseLineEdit_);
	theBrowseLayout_->addWidget(theBrowseBtn_);

	this->GetWindowLayout()->insertLayout(this->GetWindowLayout()->count() - 2, theBrowseLayout_);

	connect(theBrowseLineEdit_, SIGNAL(returnPressed()), this, SLOT(ShowParallelOptions()));
}

AutLib::LoadSimulationWindow::~LoadSimulationWindow()
{
	if (theBrowseLabel_)
	{
		delete theBrowseLabel_;
		theBrowseLabel_ = NULL;
	}

	if (theBrowseLineEdit_)
	{
		delete theBrowseLineEdit_;
		theBrowseLineEdit_ = NULL;
	}

	if (theBrowseBtn_)
	{
		delete theBrowseBtn_;
		theBrowseBtn_ = NULL;
	}

	if (theBrowseLayout_)
	{
		delete theBrowseLayout_;
		theBrowseLayout_ = NULL;
	}
}