#include <TonbAddSphereDlg.hxx>
#include <Pnt3d.hxx>
#include <MainWindow.hxx>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGridLayout>

AutLib::TonbAddSphereDlg::TonbAddSphereDlg(MainWindow* parent)
	: QDialog(parent)
{
	setWindowTitle(QMainWindow::tr("Create Sphere Part"));
	setWindowIcon(QIcon(":/part/Icons/Part/Regular Shapes/Sphere.png"));

	setupLayout();
}

void AutLib::TonbAddSphereDlg::setupLayout()
{
	QGridLayout* layout = new QGridLayout;

	theParametersBox_ = new QGroupBox(QMainWindow::tr("Sphere Parameters"));
	{
		QLabel* centerLabel = new QLabel("Origin");

		theCenterX_ = new QLineEdit("0.0");
		theCenterY_ = new QLineEdit("0.0");
		theCenterZ_ = new QLineEdit("0.0");
		theRadiusLineEdit_ = new QLineEdit("1.0");

		QLabel* X0Label = new QLabel("X");
		QLabel* Y0Label = new QLabel("Y");
		QLabel* Z0Label = new QLabel("Z");
		QLabel* RadiusLabel = new QLabel("Radius");

		layout->addWidget(centerLabel, 0, 1, 1, 1, Qt::AlignHCenter);
		layout->addWidget(X0Label, 1, 0, 1, 1, Qt::AlignHCenter);
		layout->addWidget(theCenterX_, 1, 1, 1, 1, Qt::AlignHCenter);
		layout->addWidget(Y0Label, 2, 0, 1, 1, Qt::AlignHCenter);
		layout->addWidget(theCenterY_, 2, 1, 1, 1, Qt::AlignHCenter);
		layout->addWidget(Z0Label, 3, 0, 1, 1, Qt::AlignHCenter);
		layout->addWidget(theCenterZ_, 3, 1, 1, 1, Qt::AlignHCenter);

		layout->addWidget(RadiusLabel, 4, 1, 1, 1, Qt::AlignHCenter);
		layout->addWidget(theRadiusLineEdit_, 5, 1, 1, 1, Qt::AlignHCenter);

		theParametersBox_->setLayout(layout);
	}

	QHBoxLayout* ButtonsLayout = new QHBoxLayout;
	{
		theBtnOK_ = new QPushButton(QMainWindow::tr("OK"));
		theBtnCancel_ = new QPushButton(QMainWindow::tr("Cancel"));

		ButtonsLayout->addStretch(1);
		ButtonsLayout->addWidget(theBtnOK_);
		ButtonsLayout->addWidget(theBtnCancel_);
	}

	theMainLayout_ = new QVBoxLayout;
	{
		theMainLayout_->addWidget(theParametersBox_);
		theMainLayout_->addLayout(ButtonsLayout);
	}

	setLayout(theMainLayout_);

	connect(theBtnOK_, SIGNAL(clicked()), this, SLOT(onOK()));
	connect(theBtnCancel_, SIGNAL(clicked()), this, SLOT(reject()));
}

void AutLib::TonbAddSphereDlg::onOK()
{
	theOrigin_ = new Pnt3d(theCenterX_->text().toDouble(), theCenterY_->text().toDouble(), theCenterZ_->text().toDouble());
	theRadius_ = theRadiusLineEdit_->text().toDouble();

	accept();
}

void AutLib::TonbAddSphereDlg::keyPressEvent(QKeyEvent * event)
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