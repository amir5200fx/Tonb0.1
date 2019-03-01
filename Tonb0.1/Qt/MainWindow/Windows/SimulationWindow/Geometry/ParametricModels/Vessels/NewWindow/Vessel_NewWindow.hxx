#pragma once
#ifndef _Vessel_NewWindow_Header
#define _Vessel_NewWindow_Header

//#include <QtWidgets/qmainwindow.h>
//
//class QRadioButton;
//class QVBoxLayout;
//class QGroupBox;
//class QPushButton;
//class QHBoxLayout;
//
//namespace AutLib
//{
//
//	class TonbVesselsTreeWidgetItem;
//
//	class Vessel_NewWindow
//		: public QMainWindow
//	{
//		Q_OBJECT
//
//	private:
//
//		QRadioButton* theRadioBtn1_ = NULL;
//		QRadioButton* theRadioBtn2_ = NULL;
//		QRadioButton* theRadioBtn3_ = NULL;
//		QVBoxLayout* theLayout_Group_ = NULL;
//		QGroupBox* the_GroupBox_ = NULL;
//		QGroupBox* the_EnabledGroupBox_ = NULL;
//		QVBoxLayout* theEnabledLayout_ = NULL;
//		QHBoxLayout* theContainerLayout_ = NULL;
//		QVBoxLayout* the_Layout_ = NULL;
//
//		QPushButton* theBtnClose_ = NULL;
//		QPushButton* theBtnHelp_ = NULL;
//		QHBoxLayout* theBtnLayout_ = NULL;
//
//	public:
//
//		Vessel_NewWindow(TonbVesselsTreeWidgetItem* parent = 0);
//
//	public slots:
//
//		void ShowNewWindow();
//	};
//}

#include <QtWidgets/QWizardPage>

class QRadioButton;
class QVBoxLayout;
class QHBoxLayout;
class QGroupBox;
class QLabel;


namespace AutLib
{

	struct Page1Elements
	{
		QRadioButton* theRadioBtn1_ = NULL;
		QRadioButton* theRadioBtn2_ = NULL;
		QRadioButton* theRadioBtn3_ = NULL;
		QVBoxLayout* theLayout_Group_ = NULL;
		QGroupBox* the_GroupBox_ = NULL;
		QLabel* theImage_ = NULL;
		QHBoxLayout* theContainerLayout_ = NULL;
	};

	class TonbVesselsTreeWidgetItem;

	class Vessel_NewWindow
		: public QWizard
	{

		Q_OBJECT

	private:

		TonbVesselsTreeWidgetItem* theParentItem_ = NULL;

		Page1Elements* thePage1Elements_ = NULL;

	public:

		Vessel_NewWindow(QWidget* parentwindow = 0, TonbVesselsTreeWidgetItem* parent = 0);


		QWizardPage* CreatePage1();

		QWizardPage* CreatePage2();

	public slots:
		
		void ShowNewWindow();

	private slots:

		void UpdateRadioBtnPage1();

		void CloseWindowSlot(int result);
	};
}

#endif // !_Vessel_NewWindow_Header
