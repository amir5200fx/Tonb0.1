#pragma once
#ifndef _LoadSimulationWindow_Header
#define _LoadSimulationWindowHeader

#include <NewSimulationWindow.hxx>

class QLabel;
class QLineEdit;
class QHBoxLayout;

namespace AutLib
{

	class LoadSimulationWindow
		: public NewSimulationWindow
	{

	private:

		QLabel* theBrowseLabel_ = NULL;
		QLineEdit* theBrowseLineEdit_ = NULL;
		QPushButton* theBrowseBtn_ = NULL;
		QHBoxLayout* theBrowseLayout_ = NULL;

	public:

		LoadSimulationWindow(QMainWindow* parent);

		~LoadSimulationWindow();
	};
}
#endif // !_LoadSimulationWindow_Header
