#pragma once
#ifndef _TonbAddSphereDlg_Header
#define _TonbAddSphereDlg_Header

#include <QtWidgets/QDialog>

class QGroupBox;
class QLabel;
class QVBoxLayout;
class QPushButton;
class QLineEdit;

namespace AutLib
{
	class Pnt3d;
	class MainWindow;

	class TonbAddSphereDlg
		: public QDialog
	{
		Q_OBJECT

	public:
		
		TonbAddSphereDlg(MainWindow* parent = nullptr);

		Pnt3d* GetOrigin() const { return theOrigin_; }
		double GetRadius() const { return theRadius_; }

	private:

		Pnt3d* theOrigin_ = nullptr;
		double theRadius_;

		QLineEdit* theCenterX_ = nullptr;
		QLineEdit* theCenterY_ = nullptr;
		QLineEdit* theCenterZ_ = nullptr;

		QLineEdit* theRadiusLineEdit_ = nullptr;

		QGroupBox* theParametersBox_ = nullptr;

		QPushButton* theBtnOK_ = nullptr;
		QPushButton* theBtnCancel_ = nullptr;

		QVBoxLayout* theMainLayout_ = nullptr;

		void setupLayout();

	private slots:

		void onOK();

	protected:

		void keyPressEvent(QKeyEvent *event);

	};
}

#endif // !_TonbAddSphereDlg_Header
