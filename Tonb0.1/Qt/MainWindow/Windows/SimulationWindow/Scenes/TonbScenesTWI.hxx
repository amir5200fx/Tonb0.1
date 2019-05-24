#pragma once
#ifndef _TonbScenesTWI_Header
#define _TonbScenesTWI_Header

#include <TonbTWI.hxx>
#include <QtCore/qobject.h>

namespace AutLib
{

	class TonbSceneItem;
	class TonbPartTWI;

	class TonbScenesTWI
		: public TonbTWI
	{

		Q_OBJECT

		struct ScenesContextMenu
		{
			QAction* theNewAction_ = NULL;

			QMenu* theNewSubMenu_ = NULL;
			QAction* theNewGeometryAction_ = NULL;
		};

	private:

		QList<std::shared_ptr<TonbSceneItem>> theScenes_;

		std::shared_ptr<ScenesContextMenu> theContextMenu_ = NULL;

		void CreateMenu();

	public:

		TonbScenesTWI(SimulationWindow* parentwindow = 0, TonbSimulationTreeWidget* parent = 0, const QString& title = "");

		int GetNumberOfScenes() const
		{
			return theScenes_.size();
		}

		std::shared_ptr<TonbSceneItem> GetScene(const QString& sceneName) const;

		QList<std::shared_ptr<TonbSceneItem>> GetScenes() const
		{
			return theScenes_;
		}

		QList<std::shared_ptr<TonbSceneItem>>& GetScenes()
		{
			return theScenes_;
		}

		int GetSceneIndex(const QString& sceneName) const;

		void AddScene(const QString& partName);

		void AddScene(std::shared_ptr<TonbSceneItem> scene);

		void AddScene(std::shared_ptr<TonbPartTWI> scene);

		void RemoveScene(const QString& sceneName);

		void RemoveScene(std::shared_ptr<TonbSceneItem> scene);

		void RemoveSceneAt(int Index);

	public slots:

		void NewItemSlot();
	};
}

#endif // !_TonbScenesTWI_Header
