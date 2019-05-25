#pragma once
#ifndef _TonbSceneItem_Header
#define _TonbSceneItem_Header

#include <TonbTWI.hxx>
#include <QVTKOpenGLNativeWidget.h>
#include <QtWidgets/qmenu.h>

class vtkCamera;
class vtkActor;
class customMouseInteractorStyle;
class vtkGenericOpenGLRenderWindow;
class vtkTextActor;

namespace AutLib
{

	class TonbSimulationTreeWidget;
	class TonbPartTWI;
	class SimulationWindow;

	class TonbSceneItem
		: public QVTKOpenGLNativeWidget
		, public TonbTWI
		, public std::enable_shared_from_this<TonbSceneItem>
	{

		struct SceneItemContextMenu
		{
			QAction* theRenameAction_ = NULL;

			QAction* theExportSceneAction_ = NULL;

			QAction* theSnapshotAction_ = NULL;
		};

		struct SceneContextMenu
		{
			QMenu* theSeneMenu_ = NULL;

			QAction* theHideAction_ = NULL;

			QAction* theShowAllAction_ = NULL;

			SceneContextMenu(QWidget* parent = nullptr)
			{
				theSeneMenu_ = new QMenu(parent);
			}
		};

	private:

		vtkSmartPointer<vtkRenderer> theRenderer_;

		vtkSmartPointer<vtkGenericOpenGLRenderWindow> theRenderWindow_;

		vtkSmartPointer<vtkRenderWindowInteractor> theRenderWindowInteractor_;

		vtkSmartPointer<customMouseInteractorStyle> theInteractorStyle_;

		vtkSmartPointer<vtkCamera> theCamera_;

		vtkSmartPointer<vtkTextActor> theLogoActor_;

		QList<vtkSmartPointer<vtkActor>> theGeometry_;

		QList<std::shared_ptr<TonbPartTWI>> theParts_;

		std::shared_ptr<SceneItemContextMenu> theSceneItemContextMenu_ = NULL;

		std::shared_ptr<SceneContextMenu> theSceneContextMenu_ = NULL;

		void CreateMenu();
		
	public:

		TonbSceneItem(SimulationWindow* parentwindow = 0, TonbTWI* parent = 0, const QString& title = "");

		virtual ~TonbSceneItem(){}

		void StartScene();

		std::shared_ptr<TonbPartTWI> GetPart(const QString& partName) const;

		void AddPart(std::shared_ptr<TonbPartTWI> part);

		void CreateGeometry();

		void UpdateExportContextMenu();

		void AddActorToSelectedActors(vtkActor* actor);

		void SetSelectedActorColor(QColor color);

	public slots:

		void SetOpacitySlot(int value);

		void SnapshotSlot() override;

		//void RenameItemSlot();

		void onCustomContextMenuRequested(const QPoint& pos) override;

		void HideObjectSlot() override;

		void ShowAllObjectSlot() override;

		void UpdateGeometryColorSlot(QtProperty * property, const QVariant & val) override;

		void onDoubleClickSlot(QTreeWidgetItem* item, int col) override;

	};
}

#endif // !_TonbSceneItem_Header
