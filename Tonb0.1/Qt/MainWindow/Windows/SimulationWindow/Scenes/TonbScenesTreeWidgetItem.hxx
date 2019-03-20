#pragma once
#ifndef _TonbScenesTreeWidgetItem_Header
#define _TonbScenesTreeWidgetItem_Header

#include <TonbTreeWidgetItem.hxx>
#include <QtCore/qobject.h>

namespace AutLib
{

	class TonbSceneItem;
	class TonbPartTreeWidgetItem;

	class TonbScenesTreeWidgetItem
		: public TonbTreeWidgetItem
	{

		Q_OBJECT

		struct ScenesContextMenu
		{
			QAction* theNewAction_ = NULL;

			QMenu* theNewSubMenu_ = NULL;
			QAction* theNewGeometryAction_ = NULL;
		};

	private:

		QList<TonbSceneItem*> theScenes_;

		ScenesContextMenu* theContextMenu_ = NULL;

		void CreateMenu();

	public:

		TonbScenesTreeWidgetItem(SimulationWindow* parentwindow = 0, TonbSimulationTreeWidget* parent = 0, const QString& title = "");

		int GetNumberOfScenes() const
		{
			return theScenes_.size();
		}

		TonbSceneItem* GetScene(const QString& sceneName) const;

		QList<TonbSceneItem*> GetScenes() const
		{
			return theScenes_;
		}

		QList<TonbSceneItem*>& GetScenes()
		{
			return theScenes_;
		}

		int GetSceneIndex(const QString& sceneName) const;

		void AddScene(const QString& partName);

		void AddScene(TonbSceneItem* scene);

		void AddScene(TonbPartTreeWidgetItem* scene);

		void RemoveScene(const QString& sceneName);

		void RemoveScene(TonbSceneItem* scene);

		void RemoveSceneAt(int Index);

	public slots:

		void NewItemSlot();
	};
}

#endif // !_TonbScenesTreeWidgetItem_Header
