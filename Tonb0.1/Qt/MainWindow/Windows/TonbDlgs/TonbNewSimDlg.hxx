#pragma once
#ifndef _TonbNewSimDlg_Header
#define _TonbNewSimDlg_Header

#include <QtWidgets/QDialog>

class QGroupBox;
class QVBoxLayout;
class QHBoxLayout;
class QRadioButton;
class QLabel;
class QSpinBox;
class QPushButton;
class QLineEdit;

namespace AutLib
{

	class MainWindow;

	class TonbNewSimDlg
		: public QDialog
	{
		Q_OBJECT

	private:

		QRadioButton* theRadioBtn1_ = nullptr;
		QRadioButton* theRadioBtn2_ = nullptr;
		QVBoxLayout* theLayout_MPI_Group_ = nullptr;
		QGroupBox* theMPI_GroupBox_ = nullptr;
		QVBoxLayout* the_Layout_NewSim_ = nullptr;

		QLabel* theParallelLabel_ = nullptr;
		QSpinBox* theParallelSpin_ = nullptr;
		QHBoxLayout* theParallelLayout_ = nullptr;

		QPushButton* theBtnOK_ = nullptr;
		QPushButton* theBtnCancel_ = nullptr;
		QHBoxLayout* theBtnLayout_ = nullptr;

		void setupLayout();

	public:

		TonbNewSimDlg(MainWindow* parent = nullptr);

		//~TonbNewSimDlg();

		QVBoxLayout* GetWindowLayout() const
		{
			return the_Layout_NewSim_;
		}

		QVBoxLayout*& GetWindowLayout()
		{
			return the_Layout_NewSim_;
		}
	
	private slots:
		void onOK();

	public slots:

		void ShowParallelOptions();

	protected:

		void keyPressEvent(QKeyEvent *event);
	};
}

#endif // !_TonbNewSimDlg_Header