#pragma once
#ifndef _TonbSceneItem_Header
#define _TonbSceneItem_Header

#include <TonbTreeWidgetItem.hxx>
#include <QVTKOpenGLNativeWidget.h>

class vtkCamera;
class customMouseInteractorStyle;
class vtkGenericOpenGLRenderWindow;

namespace AutLib
{

	class TonbSimulationTreeWidget;
	class SimulationWindow;

	class TonbSceneItem
		//: public TonbTreeWidgetItem
		: public QVTKOpenGLNativeWidget
	{

	private:

		vtkSmartPointer<vtkRenderer> theRenderer_;

		vtkSmartPointer<vtkGenericOpenGLRenderWindow> theRenderWindow_;

		vtkSmartPointer<vtkRenderWindowInteractor> theRenderWindowInteractor_;

		vtkSmartPointer<customMouseInteractorStyle> theInteractorStyle_;

		vtkSmartPointer<vtkCamera> theCamera_;
		
	public:

		TonbSceneItem(SimulationWindow* parentwindow = 0, TonbSimulationTreeWidget* parent = 0, const QString& title = "");

		virtual ~TonbSceneItem(){}

		void RenderTheRenderWindow();

		void StartRenderWindowInteractor();

		void StartScene();

	};
}

#endif // !_TonbSceneItem_Header
