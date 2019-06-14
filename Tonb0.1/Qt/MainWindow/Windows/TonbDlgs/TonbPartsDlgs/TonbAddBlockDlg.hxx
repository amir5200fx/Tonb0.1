#pragma once
#ifndef _TonbAddBlockDlg_Header
#define _TonbAddBlockDlg_Header

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

	class TonbAddBlockDlg
		: public QDialog
	{
		Q_OBJECT

	public:

		TonbAddBlockDlg(MainWindow* parent = nullptr);

		Pnt3d* GetP0() const { return theP0_; }
		Pnt3d* GetP1() const { return theP1_; }

	private:

		Pnt3d* theP0_ = nullptr;
		Pnt3d* theP1_ = nullptr;

		QLineEdit*theP0X_ = nullptr;			QLineEdit*theP1X_ = nullptr;
		QLineEdit*theP0Y_ = nullptr;			QLineEdit*theP1Y_ = nullptr;
		QLineEdit*theP0Z_ = nullptr;			QLineEdit*theP1Z_ = nullptr;

		QGroupBox* theCoordinatesBox_ = nullptr;

		QVBoxLayout* theMainLayout_ = nullptr;

		QPushButton* theBtnOK_ = nullptr;
		QPushButton* theBtnCancel_ = nullptr;

		void setupLayout();

	private slots:

		void onOK();

	protected:

		void keyPressEvent(QKeyEvent *event);
	};
}

#endif // !_TonbAddBlockDlg_Header
