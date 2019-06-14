#pragma once
#ifndef _TonbNewSimDlg_Header
#define _TonbNewSimDlgHeader

#include <TonbNewSimDlg.hxx>

class QLabel;
class QLineEdit;
class QHBoxLayout;

namespace AutLib
{

	class MainWindow;

	class TonbLoadSimDlg
		: public TonbNewSimDlg
	{

	private:

		QLabel* theBrowseLabel_ = nullptr;
		QLineEdit* theBrowseLineEdit_ = nullptr;
		QPushButton* theBrowseBtn_ = nullptr;
		QHBoxLayout* theBrowseLayout_ = nullptr;

	public:

		TonbLoadSimDlg(MainWindow* parent = nullptr);

		//~LoadSimulationDlg();
	};
}
#endif // !_LoadSimulationWindow_Header
