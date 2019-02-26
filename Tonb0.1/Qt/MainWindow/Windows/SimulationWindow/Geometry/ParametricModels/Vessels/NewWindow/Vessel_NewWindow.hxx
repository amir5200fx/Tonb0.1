#pragma once
#ifndef _Vessel_NewWindow_Header
#define _Vessel_NewWindow_Header

#include <QtWidgets/qmainwindow.h>

class QRadioButton;
class QVBoxLayout;
class QGroupBox;
class QPushButton;
class QHBoxLayout;

namespace AutLib
{

	class TonbVesselsTreeWidgetItem;

	class Vessel_NewWindow
		: public QMainWindow
	{
		Q_OBJECT

	private:

		QRadioButton* theRadioBtn1_ = NULL;
		QRadioButton* theRadioBtn2_ = NULL;
		QRadioButton* theRadioBtn3_ = NULL;
		QVBoxLayout* theLayout_Group_ = NULL;
		QGroupBox* the_GroupBox_ = NULL;
		QGroupBox* the_EnabledGroupBox_ = NULL;
		QVBoxLayout* theEnabledLayout_ = NULL;
		QHBoxLayout* theContainerLayout_ = NULL;
		QVBoxLayout* the_Layout_ = NULL;

		QPushButton* theBtnClose_ = NULL;
		QPushButton* theBtnHelp_ = NULL;
		QHBoxLayout* theBtnLayout_ = NULL;

	public:

		Vessel_NewWindow(TonbVesselsTreeWidgetItem* parent = 0);

	public slots:

		void ShowNewWindow();
	};
}

#endif // !_Vessel_NewWindow_Header
