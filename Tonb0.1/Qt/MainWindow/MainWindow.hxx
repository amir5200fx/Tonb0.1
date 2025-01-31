#pragma once
#ifndef _MainWindow_Header
#define _MainWindow_Header

#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qapplication.h>
#include <Menu_File.hxx>
#include <QtGui/QKeyEvent>
#include <TonbLoadSimDlg.hxx>
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
class QProgressBar;

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
		, public std::enable_shared_from_this<MainWindow>
	{
		Q_OBJECT

	private:

		//std::shared_ptr<NewSimulationWindow> theNewSimWindow_;

		//std::shared_ptr<LoadSimulationWindow> theLoadSimWindow_;

		std::shared_ptr<SimulationWindow> theSimulationWindow_;

		QList<std::shared_ptr<QDockWidget>> theDockWidgets_;

		std::shared_ptr<QProgressBar> theProgressBar_;

		std::shared_ptr<AppData> theAppData_;

		bool AppIsSaved_ = true;

		//TonbSceneItem* theScene_ = NULL;

		//QSlider* theSlider_ = NULL;

	public:

		MainWindow(QWidget* parent = 0);

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

		std::shared_ptr<QDockWidget> GetPropertyDock() const
		{
			for (int i = 0; i < theDockWidgets_.size(); i++)
			{
				if (theDockWidgets_[i]->objectName() == "Properties Window")
					return theDockWidgets_[i];
			}
		}

		std::shared_ptr<QDockWidget>& GetPropertyDock()
		{
			for (int i = 0; i < theDockWidgets_.size(); i++)
			{
				if (theDockWidgets_[i]->objectName() == "Properties Window")
					return theDockWidgets_[i];
			}
		}

	protected:


	public slots:

		//void NewSimulationWindowClosedSlot(int result);

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
