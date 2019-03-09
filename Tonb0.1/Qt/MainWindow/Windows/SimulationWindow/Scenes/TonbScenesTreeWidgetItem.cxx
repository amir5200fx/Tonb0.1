#include <TonbScenesTreeWidgetItem.hxx>
#include <TonbSceneItem.hxx>
#include <QtWidgets/qmenu.h>
#include <QtWidgets/qaction.h>

AutLib::TonbScenesTreeWidgetItem::TonbScenesTreeWidgetItem(SimulationWindow * parentwindow, TonbSimulationTreeWidget * parent, const QString & title)
	: TonbTreeWidgetItem(parentwindow, parent, title)
{
	this->CreateMenu();
}

AutLib::TonbSceneItem * AutLib::TonbScenesTreeWidgetItem::GetScene(const QString & sceneName) const
{
	for (int i = 0; i < theScenes_.size(); i++)
	{
		if (sceneName == theScenes_.at(i)->text(0))
			return theScenes_.at(i);
	}
}

int AutLib::TonbScenesTreeWidgetItem::GetSceneIndex(const QString & sceneName) const
{
	for (int i = 0; i < theScenes_.size(); i++)
	{
		if (sceneName == theScenes_.at(i)->text(0))
			return i;
	}
	return -1;
}

void AutLib::TonbScenesTreeWidgetItem::AddScene(const QString & sceneName)
{
	theScenes_.push_back(new TonbSceneItem((SimulationWindow*)this->GetParentWindow(), this, sceneName));
}

void AutLib::TonbScenesTreeWidgetItem::AddScene(TonbSceneItem * scene)
{
	theScenes_.push_back(scene);
}

void AutLib::TonbScenesTreeWidgetItem::RemoveScene(const QString & sceneName)
{
	theScenes_.removeAt(GetSceneIndex(sceneName));
}

void AutLib::TonbScenesTreeWidgetItem::RemoveScene(TonbSceneItem * scene)
{
	theScenes_.removeAt(GetSceneIndex(scene->text(0)));
}

void AutLib::TonbScenesTreeWidgetItem::RemoveSceneAt(int Index)
{
	theScenes_.removeAt(Index);
}

void AutLib::TonbScenesTreeWidgetItem::CreateMenu()
{
	theContextMenu_ = new ScenesContextMenu;

	theContextMenu_->theNewAction_ = new QAction("New", (QWidget*)this->GetParentWindow());

	theContextMenu_->theNewSubMenu_ = new QMenu((QWidget*)this->GetParentWindow());

	theContextMenu_->theNewGeometryAction_ = new QAction("Geometry", (QWidget*)this->GetParentWindow());

	theContextMenu_->theNewSubMenu_->addAction(theContextMenu_->theNewGeometryAction_);

	theContextMenu_->theNewAction_->setMenu(theContextMenu_->theNewSubMenu_);

	GetContextMenu()->addAction(theContextMenu_->theNewAction_);

	QObject::connect(theContextMenu_->theNewGeometryAction_, SIGNAL(triggered()), this, SLOT(NewItemSlot()));
}

void AutLib::TonbScenesTreeWidgetItem::NewItemSlot()
{
	this->AddScene("Scene");
}