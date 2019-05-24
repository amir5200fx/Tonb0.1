#pragma once
#ifndef _NewSimulationWindow_Header
#define _NewSimulationWindow_Header

#include <QtWidgets/qmainwindow.h>

class QGroupBox;
class QVBoxLayout;
class QHBoxLayout;
class QRadioButton;
class QLabel;
class QSpinBox;
class QPushButton;

namespace AutLib
{

	class MainWindow;

	class NewSimulationWindow
		: public QMainWindow
	{
		Q_OBJECT

	private:

		QRadioButton* theRadioBtn1_ = NULL;
		QRadioButton* theRadioBtn2_ = NULL;
		QVBoxLayout* theLayout_MPI_Group_ = NULL;
		QGroupBox* theMPI_GroupBox_ = NULL;
		QVBoxLayout* the_Layout_NewSim_ = NULL;

		QLabel* theParallelLabel_ = NULL;
		QSpinBox* theParallelSpin_ = NULL;
		QHBoxLayout* theParallelLayout_ = NULL;

		QPushButton* theBtnOK_ = NULL;
		QPushButton* theBtnCancel_ = NULL;
		QHBoxLayout* theBtnLayout_ = NULL;

		void CreateNewWindow();

	public:

		NewSimulationWindow(MainWindow* parent = NULL);

		~NewSimulationWindow();

		QVBoxLayout* GetWindowLayout() const
		{
			return the_Layout_NewSim_;
		}

		QVBoxLayout*& GetWindowLayout()
		{
			return the_Layout_NewSim_;
		}

	signals:

		void BtnOKisClickedSignal(int);

	public slots:

		void ShowParallelOptions();

		void BtnOKisClicked();

		void BtnCancelisClicked();

	protected:

		void keyPressEvent(QKeyEvent *event);
	};
}

#endif // !_NewSimulationWindow_Header