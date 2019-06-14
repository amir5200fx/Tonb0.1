#include <TonbLoadSimDlg.hxx>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qmainwindow.h>

AutLib::TonbLoadSimDlg::TonbLoadSimDlg(MainWindow* parent)
	:TonbNewSimDlg(parent)
{
	this->setWindowTitle(QMainWindow::tr("Load Simulation"));

	setWindowIcon(QIcon(":/Menus/Icons/Menus/File/Load.png"));

	theBrowseLabel_ = new QLabel(QMainWindow::tr("File"));
	theBrowseBtn_ = new QPushButton(QMainWindow::tr("Browse"));
	theBrowseLineEdit_ = new QLineEdit;
	theBrowseLayout_ = new QHBoxLayout;
	
	theBrowseLayout_->addWidget(theBrowseLabel_);
	theBrowseLayout_->addWidget(theBrowseLineEdit_);
	theBrowseLayout_->addWidget(theBrowseBtn_);

	this->GetWindowLayout()->insertLayout(this->GetWindowLayout()->count() - 2, theBrowseLayout_);

	connect(theBrowseLineEdit_, SIGNAL(returnPressed()), this, SLOT(ShowParallelOptions()));
}

//AutLib::TonbLoadSimDlg::~TonbLoadSimDlg()
//{
//	if (theBrowseLabel_)
//	{
//		delete theBrowseLabel_;
//		theBrowseLabel_ = NULL;
//	}
//
//	if (theBrowseLineEdit_)
//	{
//		delete theBrowseLineEdit_;
//		theBrowseLineEdit_ = NULL;
//	}
//
//	if (theBrowseBtn_)
//	{
//		delete theBrowseBtn_;
//		theBrowseBtn_ = NULL;
//	}
//
//	if (theBrowseLayout_)
//	{
//		delete theBrowseLayout_;
//		theBrowseLayout_ = NULL;
//	}
//}