#pragma once
#ifndef _MainWindow_Header
#define _MainWindow_Header

#include<QtWidgets/qmainwindow.h>
#include<Menu_File.hxx>
#include <iostream>

using namespace std;

//namespace Ui {
//	class MainWindow;
//}
namespace AutLib
{
	class MainWindow
		: public QMainWindow
		, public Menu_File
	{
		Q_OBJECT

	private:

		void SetParent();

		//Ui::MainWindow *ui;

	public:

		explicit MainWindow(QWidget* parent = 0);

		~MainWindow()
		{}

	protected:

		//void closeEvent(QCloseEvent* event);
//#ifndef QT_NO_CONTEXTMENU
//		void contextMenuEvent(QContextMenuEvent *event) override;
//#endif // QT_NO_CONTEXTMENU

	public slots:

		void NewSimulationf() { cout << "New Simulation is clicked\n"; }

		void LoadSimulationf() { cout << "Load Simulation is clicked\n"; }

		void Savef(){}

		void SaveAsf(){}

		void SaveAllf(){}

		void AutoSavef(){}

		void Macrof(){}

		void Importf(){}

		void Exportf(){}

		void PageSetupf(){}

		void Printf(){}

		void Exitf(){}

	};
}

#endif // !_MainWindow_Header
