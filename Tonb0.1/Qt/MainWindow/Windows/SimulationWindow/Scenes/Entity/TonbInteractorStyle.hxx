#pragma once
#ifndef _TonbInteractorStyle_Header
#define _TonbInteractorStyle_Header

#include <vtkInteractorStyleTrackballCamera.h>
#include <QtCore/QList>
#include <vtkObjectFactory.h>

class QColor;
class vtkActor;

namespace AutLib
{
	class TonbSceneItem;

	class TonbInteractorStyle
		: public vtkInteractorStyleTrackballCamera
	{
	private:

		QList<vtkActor*> theSelectedActors_;

		QList<vtkActor*> theHiddenActors_;

		TonbSceneItem* theParent_ = nullptr;

		int PreviousPosition[2];
		int ResetPixelDistance;

		vtkTypeMacro(TonbInteractorStyle, vtkInteractorStyleTrackballCamera);

	public:

		TonbInteractorStyle();

		static TonbInteractorStyle* New();

		void SetParent(TonbSceneItem* parent)
		{
			theParent_ = parent;
		}

		void SetSelectedActorColor(QColor color);

		void AddActorToSelectedActors(vtkActor* actor);

		void HideSelectedActors();

		void ShowAllActors();

		virtual void OnLeftButtonUp() override;

		virtual void OnLeftButtonDown() override;

		virtual void OnMouseWheelForward() override;

		virtual void OnMouseWheelBackward() override;

		virtual void OnMiddleButtonDown() override;

		virtual void OnRightButtonDown() override;

		virtual void OnRightButtonUp() override;

		virtual void OnChar() override;

		QList<vtkActor*> GetSelectedActors() const
		{
			return theSelectedActors_;
		}

		QList<vtkActor*>& GetSelectedActors()
		{
			return theSelectedActors_;
		}

		static QColor GeometryColorRGB;
		static QColor GeometrySelectedColorRGB;

	};
	//vtkStandardNewMacro(TonbInteractorStyle);
}

#endif // !_TonbInteractorStyle_Header
