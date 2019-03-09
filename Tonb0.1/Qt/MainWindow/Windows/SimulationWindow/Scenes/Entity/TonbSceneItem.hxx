#pragma once
#ifndef _TonbSceneItem_Header
#define _TonbSceneItem_Header

#include <TonbTreeWidgetItem.hxx>
#include <QVTKOpenGLNativeWidget.h>

class vtkCamera;
class vtkActor;
class customMouseInteractorStyle;
class vtkGenericOpenGLRenderWindow;

namespace AutLib
{

	class TonbSimulationTreeWidget;
	class SimulationWindow;

	class TonbSceneItem
		: public QVTKOpenGLNativeWidget
		, public TonbTreeWidgetItem
	{

		struct SceneContextMenu
		{
			QAction* theRenameAction_ = NULL;
		};

		Q_OBJECT

	private:

		vtkSmartPointer<vtkRenderer> theRenderer_;

		vtkSmartPointer<vtkGenericOpenGLRenderWindow> theRenderWindow_;

		vtkSmartPointer<vtkRenderWindowInteractor> theRenderWindowInteractor_;

		vtkSmartPointer<customMouseInteractorStyle> theInteractorStyle_;

		vtkSmartPointer<vtkCamera> theCamera_;

		vtkSmartPointer<vtkActor> theGeometry_;

		SceneContextMenu* theContextMenu_ = NULL;

		void CreateMenu();
		
	public:

		TonbSceneItem(SimulationWindow* parentwindow = 0, TonbTreeWidgetItem* parent = 0, const QString& title = "");

		virtual ~TonbSceneItem(){}

		void RenderTheRenderWindow();

		void StartRenderWindowInteractor();

		void StartScene();

	public slots:

		void SetOpacitySlot(int value);

		void RenameItemSlot();

	};
}

#endif // !_TonbSceneItem_Header
