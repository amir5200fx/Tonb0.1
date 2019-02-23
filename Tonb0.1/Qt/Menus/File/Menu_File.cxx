#include <Menu_File.hxx>
#include <QtWidgets/qaction.h>
#include <QtWidgets/qmenu.h>
#include <QtWidgets/qtoolbar.h>

AutLib::Menu_File::Menu_File(QMainWindow* parent)
	: theParent_(parent)
{
}

void AutLib::Menu_File::createActions()
{
	/* Section New & Load*/
	theNew_ = new QAction(QIcon(":/Menus/Icons/Menus/File/New.png"), QMainWindow::tr("&New Simulation"), theParent_);
	theNew_->setShortcut(QMainWindow::tr("Ctrl+N"));
	theNew_->setStatusTip(QMainWindow::tr("Create a new simulation file"));
	QMainWindow::connect(theNew_, SIGNAL(triggered()), theParent_, SLOT(NewSimulationSlot()));

	theLoad_ = new QAction(QIcon(":/Menus/Icons/Menus/File/Load.png"), QMainWindow::tr("&Load Simulation"), theParent_);
	theLoad_->setShortcut(QMainWindow::tr("Ctrl+L"));
	theLoad_->setStatusTip(QMainWindow::tr(""));
	QMainWindow::connect(theLoad_, SIGNAL(triggered()), theParent_, SLOT(LoadSimulationSlot()));

	/* Section Save & Save As & AutoSave & SaveAll*/

	theSave_ = new QAction(QIcon(":/Menus/Icons/Menus/File/Save.png"), QMainWindow::tr("&Save"), theParent_);
	theSave_->setShortcut(QMainWindow::tr("Ctrl+S"));
	theSave_->setStatusTip(QMainWindow::tr(""));
	theSave_->setEnabled(false);
	QMainWindow::connect(theSave_, SIGNAL(triggered()), theParent_, SLOT(SaveSlot()));

	theSaveAs_ = new QAction(QIcon(":/Menus/Icons/Menus/File/SaveAs.png"), QMainWindow::tr("&Save As..."), theParent_);
	theSaveAs_->setShortcut(QMainWindow::tr("Ctrl+Shift+S"));
	theSaveAs_->setStatusTip(QMainWindow::tr(""));
	theSaveAs_->setEnabled(false);
	QMainWindow::connect(theSaveAs_, SIGNAL(triggered()), theParent_, SLOT(SaveAsSlot()));

	theAutoSave_ = new QAction(QMainWindow::tr("&Auto Save"), theParent_);
	theAutoSave_->setStatusTip(QMainWindow::tr(""));
	theAutoSave_->setEnabled(false);
	QMainWindow::connect(theAutoSave_, SIGNAL(triggered()), theParent_, SLOT(AutoSaveSlot()));

	theSaveAll_ = new QAction(QIcon(":/Menus/Icons/Menus/File/SaveAll.png"), QMainWindow::tr("&Save All"), theParent_);
	theSaveAll_->setStatusTip(QMainWindow::tr(""));
	theSaveAll_->setEnabled(false);
	QMainWindow::connect(theSaveAll_, SIGNAL(triggered()), theParent_, SLOT(SaveAllSlot()));

	/* Section Macro & Import & Export*/

	theMacro_ = new QAction(QMainWindow::tr("&Macro"), theParent_);
	theMacro_->setStatusTip(QMainWindow::tr(""));
	QMainWindow::connect(theMacro_, SIGNAL(triggered()), theParent_, SLOT(MacroSlot()));

	theImport_ = new QAction(QIcon(":/Menus/Icons/Menus/File/Import.png"), QMainWindow::tr("&Import"), theParent_);
	theImport_->setShortcut(QMainWindow::tr("Ctrl+I"));
	theImport_->setStatusTip(QMainWindow::tr(""));
	QMainWindow::connect(theImport_, SIGNAL(triggered()), theParent_, SLOT(ImportSlot()));

	theExport_ = new QAction(QIcon(":/Menus/Icons/Menus/File/Export.png"), QMainWindow::tr("&Export"), theParent_);
	theExport_->setShortcut(QMainWindow::tr("Ctrl+E"));
	theExport_->setStatusTip(QMainWindow::tr(""));
	QMainWindow::connect(theExport_, SIGNAL(triggered()), theParent_, SLOT(ExportSlot()));

	/* Section PageSetup & Print*/

	thePageSetup_ = new QAction(QMainWindow::tr("Pa&ge Setup"), theParent_);
	thePageSetup_->setShortcut(QMainWindow::tr("Ctrl+Shift+P"));
	thePageSetup_->setStatusTip(QMainWindow::tr(""));
	QMainWindow::connect(thePageSetup_, SIGNAL(triggered()), theParent_, SLOT(PageSetupSlot()));

	thePrint_ = new QAction(QMainWindow::tr("&Print"), theParent_);
	thePrint_->setShortcut(QMainWindow::tr("Ctrl+P"));
	thePrint_->setStatusTip(QMainWindow::tr(""));
	QMainWindow::connect(thePrint_, SIGNAL(triggered()), theParent_, SLOT(PrintSlot()));

	/* Section Exit*/

	theExit_ = new QAction(QIcon(":/Menus/Icons/Menus/File/Exit.png"), QMainWindow::tr("E&xit"), theParent_);
	theExit_->setShortcut(QMainWindow::tr("Ctrl+Q"));
	theExit_->setStatusTip(QMainWindow::tr(""));
	QMainWindow::connect(theExit_, SIGNAL(triggered()), theParent_, SLOT(ExitSlot()));
}

void AutLib::Menu_File::createMenu()
{
	theMenu_ = new QMenu(QMainWindow::tr("&File"), theParent_);

	theMenu_->addAction(theNew_);
	theMenu_->addAction(theLoad_);

	theMenu_->addSeparator();

	theMenu_->addAction(theSave_);
	theMenu_->addAction(theSaveAs_);
	theMenu_->addAction(theAutoSave_);
	theMenu_->addAction(theSaveAll_);

	theMenu_->addSeparator();

	theMenu_->addAction(theMacro_);
	theMenu_->addAction(theImport_);
	theMenu_->addAction(theExport_);

	theMenu_->addSeparator();

	theMenu_->addAction(thePageSetup_);
	theMenu_->addAction(thePrint_);

	theMenu_->addSeparator();

	theMenu_->addAction(theExit_);
}

void AutLib::Menu_File::createToolbar()
{
	theToolbar_ = new QToolBar(QMainWindow::tr("File Toolbar"), theParent_);
	theToolbar_->setIconSize(QSize(25, 25));

	theToolbar_->addAction(theNew_);
	theToolbar_->addAction(theLoad_);

	theToolbar_->addSeparator();

	theToolbar_->addAction(theSave_);
	theToolbar_->addAction(theSaveAs_);

	theToolbar_->setContextMenuPolicy(Qt::PreventContextMenu);
}

void AutLib::Menu_File::Perform()
{
	createActions();
	createMenu();
	createToolbar();
}

std::string AutLib::Menu_File::GetWorkingDir()
{
	char buf[256];
	GetCurrentDirectoryA(256, buf);
	std::string out = std::string(buf) + '\\';
	out = ReplaceAll(out, std::string("\\"), std::string("/"));
	return out;
}

std::string  AutLib::Menu_File::ReplaceAll(std::string str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return str;
}
