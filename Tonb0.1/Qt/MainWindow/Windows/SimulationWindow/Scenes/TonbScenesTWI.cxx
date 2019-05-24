#include <TonbScenesTWI.hxx>
#include <TonbSceneItem.hxx>
#include <QtWidgets/qmenu.h>
#include <QtWidgets/qaction.h>
#include <TonbPartTWI.hxx>

AutLib::TonbScenesTWI::TonbScenesTWI
(
	SimulationWindow* parentwindow,
	TonbSimulationTreeWidget* parent,
	const QString & title)
	: TonbTWI(parentwindow, parent, title)
{
	this->CreateMenu();
}

std::shared_ptr<AutLib::TonbSceneItem> AutLib::TonbScenesTWI::GetScene(const QString & sceneName) const
{
	for (int i = 0; i < theScenes_.size(); i++)
	{
		if (sceneName == theScenes_.at(i)->text(0))
			return theScenes_.at(i);
	}
}

int AutLib::TonbScenesTWI::GetSceneIndex(const QString & sceneName) const
{
	for (int i = 0; i < theScenes_.size(); i++)
	{
		if (sceneName == theScenes_.at(i)->text(0))
			return i;
	}
	return -1;
}

void AutLib::TonbScenesTWI::AddScene(const QString & sceneName)
{
	theScenes_.push_back(std::make_shared<TonbSceneItem>(this->GetParentWindow(), this, sceneName));
}

void AutLib::TonbScenesTWI::AddScene(std::shared_ptr<TonbSceneItem> scene)
{
	theScenes_.push_back(scene);
}

void AutLib::TonbScenesTWI::AddScene(std::shared_ptr<TonbPartTWI> scene)
{
	AddScene(scene->text(0));
	theScenes_.at(theScenes_.size() - 1)->AddPart(scene);
	theScenes_.at(theScenes_.size() - 1)->StartScene();
}

void AutLib::TonbScenesTWI::RemoveScene(const QString & sceneName)
{
	theScenes_.removeAt(GetSceneIndex(sceneName));
}

void AutLib::TonbScenesTWI::RemoveScene(std::shared_ptr<TonbSceneItem> scene)
{
	theScenes_.removeAt(GetSceneIndex(scene->text(0)));
}

void AutLib::TonbScenesTWI::RemoveSceneAt(int Index)
{
	theScenes_.removeAt(Index);
}

void AutLib::TonbScenesTWI::CreateMenu()
{
	theContextMenu_ = std::make_shared<ScenesContextMenu>();

	theContextMenu_->theNewAction_ = new QAction("New", (QWidget*)this->GetParentWindow());

	theContextMenu_->theNewSubMenu_ = new QMenu((QWidget*)this->GetParentWindow());

	theContextMenu_->theNewGeometryAction_ = new QAction("Geometry", (QWidget*)this->GetParentWindow());

	theContextMenu_->theNewSubMenu_->addAction(theContextMenu_->theNewGeometryAction_);

	theContextMenu_->theNewAction_->setMenu(theContextMenu_->theNewSubMenu_);

	GetContextMenu()->addAction(theContextMenu_->theNewAction_);

	QObject::connect(theContextMenu_->theNewGeometryAction_, SIGNAL(triggered()), this, SLOT(NewItemSlot()));
}

void AutLib::TonbScenesTWI::NewItemSlot()
{
	this->AddScene("Scene");
}