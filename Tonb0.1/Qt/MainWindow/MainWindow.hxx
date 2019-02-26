#pragma once
#ifndef _MainWindow_Header
#define _MainWindow_Header

#include<QtWidgets/qmainwindow.h>
#include <QtWidgets/qapplication.h>
#include<Menu_File.hxx>
#include <QtGui/QKeyEvent>
#include <LoadSimulationWindow.hxx>
#include <iostream>

using namespace std;


namespace AutLib
{

	class SimulationWindow;

	class MainWindow
		: public QMainWindow
		, public Menu_File
	{
		Q_OBJECT

	private:

		NewSimulationWindow* theNewSimWindow_ = NULL;

		LoadSimulationWindow* theLoadSimWindow_ = NULL;

		SimulationWindow* theSimulationWindow_ = NULL;

	public:

		explicit MainWindow(QWidget* parent = 0);

		~MainWindow()
		{}

	protected:


	public slots:

		void NewSimulationSlot();

		void LoadSimulationSlot();

		int SaveSlot() { cout << "Save is clicked\n"; return 0; }

		void SaveAsSlot() { cout << "Save As... is clicked\n"; }

		void SaveAllSlot() { cout << "Save All is clicked\n"; }

		void AutoSaveSlot() { cout << "AutoSave is clicked\n"; }

		void MacroSlot() { cout << "Macro is clicked\n"; }

		void ImportSlot() { cout << "Import is clicked\n"; }

		void ExportSlot() { cout << "Export is clicked\n"; }

		void PageSetupSlot() { cout << "Page Setup is clicked\n"; }

		void PrintSlot() { cout << "Print is clicked\n"; }

		int ExitSlot();// { QApplication::quit(); }

		void closeEvent(QCloseEvent *event) { if(!ExitSlot()) event->ignore(); }

	};
}

#endif // !_MainWindow_Header
