#pragma once
#ifndef _TonbSceneItem_Header
#define _TonbSceneItem_Header

#include <TonbTreeWidgetItem.hxx>
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
	class TonbPartTreeWidgetItem;
	class SimulationWindow;

	class TonbSceneItem
		: public QVTKOpenGLNativeWidget
		, public TonbTreeWidgetItem
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

		QList<TonbPartTreeWidgetItem*> theParts_;

		SceneItemContextMenu* theSceneItemContextMenu_ = NULL;

		SceneContextMenu* theSceneContextMenu_ = NULL;

		void CreateMenu();
		
	public:

		TonbSceneItem(SimulationWindow* parentwindow = 0, TonbTreeWidgetItem* parent = 0, const QString& title = "");

		virtual ~TonbSceneItem(){}

		void StartScene();

		TonbPartTreeWidgetItem* GetPart(const QString& partName) const;

		void AddPart(TonbPartTreeWidgetItem* part);

		void CreateGeometry();

		void UpdateExportContextMenu();

	public slots:

		void SetOpacitySlot(int value);

		void SnapshotSlot() override;

		//void RenameItemSlot();

		void onCustomContextMenuRequested(const QPoint& pos) override;

		void HideObjectSlot() override;

		void ShowAllObjectSlot() override;

	};
}

#endif // !_TonbSceneItem_Header
