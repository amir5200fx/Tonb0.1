#include <TonbAddBlockDlg.hxx>
#include <Pnt3d.hxx>
#include <MainWindow.hxx>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGridLayout>

AutLib::TonbAddBlockDlg::TonbAddBlockDlg(MainWindow* parent)
	: QDialog(parent)
{
	setWindowTitle(QMainWindow::tr("Create Block Part"));
	setWindowIcon(QIcon(":/part/Icons/Part/Regular Shapes/Cube.png"));

	setupLayout();
}

void AutLib::TonbAddBlockDlg::setupLayout()
{
	QGridLayout* layout = new QGridLayout;

	theCoordinatesBox_ = new QGroupBox("Maximum and Minimum Coordinates");
	{
		QLabel* P0Label = new QLabel("Corner 1");              					QLabel* P1Label = new QLabel("Corner 2");

		theP0X_ = new QLineEdit("0.0");			   			   					theP1X_ = new QLineEdit("1.0");
		theP0Y_ = new QLineEdit("0.0");			   			   					theP1Y_ = new QLineEdit("1.0");
		theP0Z_ = new QLineEdit("0.0");			   			   					theP1Z_ = new QLineEdit("1.0");

		QLabel* X0Label = new QLabel("X");										QLabel* X1Label = new QLabel("X");
		QLabel* Y0Label = new QLabel("Y");										QLabel* Y1Label = new QLabel("Y");
		QLabel* Z0Label = new QLabel("Z");										QLabel* Z1Label = new QLabel("Z");

		layout->addWidget(P0Label, 0, 1, 1, 1, Qt::AlignHCenter);				layout->addWidget(P1Label, 0, 3, 1, 1, Qt::AlignHCenter);
		layout->addWidget(X0Label, 1, 0, 1, 1, Qt::AlignHCenter);				layout->addWidget(X1Label, 1, 2, 1, 1, Qt::AlignHCenter);
		layout->addWidget(theP0X_, 1, 1, 1, 1, Qt::AlignHCenter);				layout->addWidget(theP1X_, 1, 3, 1, 1, Qt::AlignHCenter);
		layout->addWidget(Y0Label, 2, 0, 1, 1, Qt::AlignHCenter);				layout->addWidget(Y1Label, 2, 2, 1, 1, Qt::AlignHCenter);
		layout->addWidget(theP0Y_, 2, 1, 1, 1, Qt::AlignHCenter);				layout->addWidget(theP1Y_, 2, 3, 1, 1, Qt::AlignHCenter);
		layout->addWidget(Z0Label, 3, 0, 1, 1, Qt::AlignHCenter);				layout->addWidget(Z1Label, 3, 2, 1, 1, Qt::AlignHCenter);
		layout->addWidget(theP0Z_, 3, 1, 1, 1, Qt::AlignHCenter);				layout->addWidget(theP1Z_, 3, 3, 1, 1, Qt::AlignHCenter);

		theCoordinatesBox_->setLayout(layout);
	}

	QHBoxLayout* buttonsLayout = new QHBoxLayout;
	{
		theBtnOK_ = new QPushButton("OK");
		theBtnCancel_ = new QPushButton("Cancel");

		buttonsLayout->addStretch(1);
		buttonsLayout->addWidget(theBtnOK_);
		buttonsLayout->addWidget(theBtnCancel_);
	}

	theMainLayout_ = new QVBoxLayout;
	{
		theMainLayout_->addWidget(theCoordinatesBox_);
		theMainLayout_->addStretch(1);
		theMainLayout_->addLayout(buttonsLayout);
	}

	setLayout(theMainLayout_);

	connect(theBtnOK_, SIGNAL(clicked()), this, SLOT(onOK()));
	connect(theBtnCancel_, SIGNAL(clicked()), this, SLOT(reject()));
}

void AutLib::TonbAddBlockDlg::onOK()
{
	theP0_ = new Pnt3d(theP0X_->text().toDouble(), theP0Y_->text().toDouble(), theP0Z_->text().toDouble());
	theP1_ = new Pnt3d(theP1X_->text().toDouble(), theP1Y_->text().toDouble(), theP1Z_->text().toDouble());

	accept();
}

void AutLib::TonbAddBlockDlg::keyPressEvent(QKeyEvent * event)
{
	switch (event->key())
	{
	case Qt::Key_Escape:
	{
		done(0);
		break;
	}
	case Qt::Key_Return:
	case Qt::Key_Enter:
	{
		onOK();
		break;
	}
	default:
		event->ignore();
	}
}