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

		NewSimulationWindow(QWidget* parent = NULL);

		~NewSimulationWindow();

		QVBoxLayout* GetWindowLayout() const
		{
			return the_Layout_NewSim_;
		}

		QVBoxLayout*& GetWindowLayout()
		{
			return the_Layout_NewSim_;
		}

	public slots:

		void ShowParallelOptions();

		void BtnOKisClicked();

	protected:

		void keyPressEvent(QKeyEvent *event);
	};
}

#endif // !_NewSimulationWindow_Header