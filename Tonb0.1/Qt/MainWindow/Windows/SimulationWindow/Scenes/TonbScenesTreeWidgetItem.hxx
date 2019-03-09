#pragma once
#ifndef _TonbScenesTreeWidgetItem_Header
#define _TonbScenesTreeWidgetItem_Header

#include <TonbTreeWidgetItem.hxx>
#include <QtCore/qobject.h>

namespace AutLib
{

	class TonbSceneItem;

	class TonbScenesTreeWidgetItem
		: public QObject
		, public TonbTreeWidgetItem
	{

		struct ScenesContextMenu
		{
			QAction* theNewAction_ = NULL;

			QMenu* theNewSubMenu_ = NULL;
			QAction* theNewGeometryAction_ = NULL;
		};

		Q_OBJECT

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

		int GetSceneIndex(const QString& sceneName) const;

		void AddScene(const QString& partName);

		void AddScene(TonbSceneItem* scene);

		void RemoveScene(const QString& sceneName);

		void RemoveScene(TonbSceneItem* scene);

		void RemoveSceneAt(int Index);

	public slots:

		void NewItemSlot();
	};
}

#endif // !_TonbScenesTreeWidgetItem_Header
