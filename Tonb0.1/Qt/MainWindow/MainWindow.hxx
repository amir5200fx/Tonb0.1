#pragma once
#ifndef _MainWindow_Header
#define _MainWindow_Header

#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qapplication.h>
#include <Menu_File.hxx>
#include <QtGui/QKeyEvent>
#include <LoadSimulationWindow.hxx>
#include <QtWidgets/qdockwidget.h>
#include <iostream>

//#include <boost/serialization/string.hpp>
//#include <boost/serialization/nvp.hpp>
//#include <boost/serialization/utility.hpp>
//#include <boost/serialization/list.hpp>
//#include <boost/serialization/version.hpp>
//#include <boost/serialization/assume_abstract.hpp>

using namespace std;

class QSlider;

namespace AutLib
{
	struct AppData
	{
		QString* theAppFileName_ = NULL;
	};

	class SimulationWindow;
	class TonbSceneItem;

	class MainWindow
		: public QMainWindow
		, public Menu_File
	{
		Q_OBJECT

	private:

		NewSimulationWindow* theNewSimWindow_ = NULL;

		LoadSimulationWindow* theLoadSimWindow_ = NULL;

		SimulationWindow* theSimulationWindow_ = NULL;

		QList<QDockWidget*> theDockWidgets_;

		AppData* theAppData_ = NULL;

		bool AppIsSaved_ = true;

		//TonbSceneItem* theScene_ = NULL;

		//QSlider* theSlider_ = NULL;

	public:

		explicit MainWindow(QWidget* parent = 0);

		~MainWindow()
		{}

		/*friend class boost::serialization::access;
		friend std::ostream & operator<<(std::ostream &os, const MainWindow &mw)
		{
			os << "Salam\n";
		}

		template<class Archive>
		void serialize(Archive &ar, const unsigned int version)
		{
			ar & BOOST_SERIALIZATION_NVP(version);
		}*/

		QDockWidget* GetPropertyDock() const
		{
			for (int i = 0; i < theDockWidgets_.size(); i++)
			{
				if (theDockWidgets_[i]->objectName() == "Properties Window")
					return theDockWidgets_[i];
			}
		}

		QDockWidget*& GetPropertyDock()
		{
			for (int i = 0; i < theDockWidgets_.size(); i++)
			{
				if (theDockWidgets_[i]->objectName() == "Properties Window")
					return theDockWidgets_[i];
			}
		}

	protected:


	public slots:

		void NewSimulationWindowClosedSlot(int result);

		void NewSimulationSlot();

		void LoadSimulationSlot();

		int SaveSlot();

		void SaveAsSlot();

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
//BOOST_CLASS_VERSION(AutLib::MainWindow, 3)

#endif // !_MainWindow_Header
