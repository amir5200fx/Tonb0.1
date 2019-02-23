#pragma once
#ifndef _Menu_File_Header
#define _Menu_File_Header

#include<QtWidgets/qmainwindow.h>
#include <string>
#include <windows.h>

namespace AutLib
{
	class Menu_File
	{

		/*Private Data*/

		QAction* theNew_;
		QAction* theLoad_;

		QAction* theSave_;
		QAction* theSaveAs_;
		QAction* theAutoSave_;
		QAction* theSaveAll_;

		QAction* theMacro_;
		QAction* theImport_;
		QAction* theExport_;

		QAction* thePageSetup_;
		QAction* thePrint_;

		QAction* theExit_;

		QMenu* theMenu_;

		QToolBar* theToolbar_;

		QMainWindow* theParent_;

		void createActions();

		void createMenu();

		void createToolbar();

	public:

		Menu_File(QMainWindow* parent = 0);

		void SetParent(QMainWindow* parent)
		{
			theParent_ = parent;
		}

		void Perform();

		static std::string GetWorkingDir();

		static std::string ReplaceAll(std::string str, const std::string& from, const std::string& to);

		QAction* New() const
		{
			return theNew_;
		}

		QAction*& New()
		{
			return theNew_;
		}

		QAction* Load() const
		{
			return theLoad_;
		}

		QAction*& Load()
		{
			return theLoad_;
		}

		QAction* Save() const
		{
			return theSave_;
		}

		QAction*& Save()
		{
			return theSave_;
		}

		QAction* SaveAs() const
		{
			return theSaveAs_;
		}

		QAction*& SaveAs()
		{
			return theSaveAs_;
		}

		QAction* SaveAll() const
		{
			return theSaveAll_;
		}

		QAction*& SaveAll()
		{
			return theSaveAll_;
		}

		QAction* AutoSave() const
		{
			return theAutoSave_;
		}

		QAction*& AutoSave()
		{
			return theAutoSave_;
		}

		QAction* Macro() const
		{
			return theMacro_;
		}

		QAction*& Macro()
		{
			return theMacro_;
		}

		QAction* Import() const
		{
			return theImport_;
		}

		QAction*& Import()
		{
			return theImport_;
		}

		QAction* Export() const
		{
			return theExport_;
		}

		QAction*& Export()
		{
			return theExport_;
		}

		QAction* PageSetup() const
		{
			return thePageSetup_;
		}

		QAction*& PageSetup()
		{
			return thePageSetup_;
		}

		QAction* Print() const
		{
			return thePrint_;
		}

		QAction*& Print()
		{
			return thePrint_;
		}

		QAction* Exit() const
		{
			return theExit_;
		}

		QAction*& Exit()
		{
			return theExit_;
		}

		QMenu* Menu() const
		{
			return theMenu_;
		}

		QMenu*& Menu()
		{
			return theMenu_;
		}

		QToolBar* Toolbar() const
		{
			return theToolbar_;
		}

		QToolBar*& Toolbar()
		{
			return theToolbar_;
		}
	};
}

#endif // !_Menu_File_Header
