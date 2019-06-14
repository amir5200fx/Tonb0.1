#include <TonbInteractorStyle.hxx>
#include <TonbSceneItem.hxx>

#include <QtGui/QColor>

#include <vtkSetGet.h>
#include <vtkSmartPointer.h>
#include <vtkNew.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkAssemblyPath.h>
#include <vtkPropPicker.h>

#include <vtkAutoInit.h>

QColor AutLib::TonbInteractorStyle::GeometryColorRGB = QColor(0.753 * 255, 0.753 * 255, 0.753 * 255);
QColor AutLib::TonbInteractorStyle::GeometrySelectedColorRGB = QColor(1.0 * 255, 0.0 * 255, 1.0 * 255);

AutLib::TonbInteractorStyle * AutLib::TonbInteractorStyle::New()
{
	VTK_STANDARD_NEW_BODY(AutLib::TonbInteractorStyle)
}

AutLib::TonbInteractorStyle::TonbInteractorStyle() : ResetPixelDistance(5)
{
	this->PreviousPosition[0] = 0;
	this->PreviousPosition[1] = 0;
}

void AutLib::TonbInteractorStyle::SetSelectedActorColor(QColor color)
{
	for (int i = 0; i < theSelectedActors_.size(); i++)
	{
		theSelectedActors_.at(i)->GetProperty()->SetColor(color.redF(), color.greenF(), color.blueF());
		vtkSmartPointer<vtkProperty> bprop =
			vtkSmartPointer<vtkProperty>::New();
		bprop->SetColor(color.redF(), color.greenF(), color.blueF());
		theSelectedActors_.at(i)->SetBackfaceProperty(bprop);
	}
}

void AutLib::TonbInteractorStyle::AddActorToSelectedActors(vtkActor* actor)
{
	for (int i = 0; i < theSelectedActors_.size(); i++)
	{
		if (theSelectedActors_.at(i) == actor)
		{
			if (this->Interactor->GetControlKey())
				theSelectedActors_.removeAt(i);
			return;
		}
	}

	theSelectedActors_.push_back(actor);
}

void AutLib::TonbInteractorStyle::HideSelectedActors()
{
	for (int i = 0; i < theSelectedActors_.size(); i++)
	{
		theSelectedActors_.at(i)->VisibilityOff();

		theSelectedActors_.at(i)->GetProperty()->SetColor(GeometryColorRGB.redF(), GeometryColorRGB.greenF(), GeometryColorRGB.blueF());
		vtkSmartPointer<vtkProperty> bprop =
			vtkSmartPointer<vtkProperty>::New();
		bprop->SetColor(GeometryColorRGB.redF(), GeometryColorRGB.greenF(), GeometryColorRGB.blueF());
		theSelectedActors_.at(i)->SetBackfaceProperty(bprop);

		theHiddenActors_.push_back(theSelectedActors_.at(i));
	}
}

void AutLib::TonbInteractorStyle::ShowAllActors()
{
	for (int i = 0; i < theHiddenActors_.size(); i++)
	{
		theHiddenActors_.at(i)->VisibilityOn();
	}
	theHiddenActors_.clear();
}

//virtual void OnLeftButtonDown()
//{
//	// Forward events
//	vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
//	if (this->CurrentRenderer == nullptr)
//	{
//		return;
//	}
//}

void AutLib::TonbInteractorStyle::OnLeftButtonUp()
{
	int pickPosition[2];
	this->GetInteractor()->GetEventPosition(pickPosition);

	int xdist = pickPosition[0] - this->PreviousPosition[0];
	int ydist = pickPosition[1] - this->PreviousPosition[1];
	int moveDistance = (int)sqrt((double)(xdist*xdist + ydist * ydist));

	if (moveDistance > this->ResetPixelDistance)
	{
		vtkInteractorStyleTrackballCamera::OnLeftButtonUp();
	}

	else
	{
		int* clickPos = this->GetInteractor()->GetEventPosition();

		// Pick from this location.
		vtkSmartPointer<vtkPropPicker>  picker =
			vtkSmartPointer<vtkPropPicker>::New();
		picker->Pick(clickPos[0], clickPos[1], 0, this->CurrentRenderer);

		double* pos = picker->GetPickPosition();

		if (picker->GetActor())
		{
			if (theSelectedActors_.size() != 0)
				SetSelectedActorColor(GeometryColorRGB);

			if (this->Interactor->GetControlKey())
				AddActorToSelectedActors(picker->GetActor());
			else
			{
				SetSelectedActorColor(GeometryColorRGB);
				theSelectedActors_.clear();

				AddActorToSelectedActors(picker->GetActor());
			}
			SetSelectedActorColor(GeometrySelectedColorRGB);

			this->CurrentRenderer->Render();
		}
		else
			if (theSelectedActors_.size() != 0)
			{
				SetSelectedActorColor(GeometryColorRGB);
				theSelectedActors_.clear();
			}

		for (int j = 0; j < theParent_->GetGeometry().size(); j++)
		{
			double opacity = 1.0;
			theParent_->GetGeometry().at(j)->GetProperty()->SetOpacity(opacity);
			theParent_->GetGeometry().at(j)->GetBackfaceProperty()->SetOpacity(opacity);
		}
		////Create a sphere
		//vtkSmartPointer<vtkSphereSource> sphereSource =
		//	vtkSmartPointer<vtkSphereSource>::New();
		//sphereSource->SetCenter(pos[0], pos[1], pos[2]);
		//sphereSource->SetRadius(0.1);

		////Create a mapper and actor
		//vtkSmartPointer<vtkPolyDataMapper> mapper =
		//	vtkSmartPointer<vtkPolyDataMapper>::New();
		//mapper->SetInputConnection(sphereSource->GetOutputPort());

		//vtkSmartPointer<vtkActor> actor =
		//	vtkSmartPointer<vtkActor>::New();
		//actor->SetMapper(mapper);

		//this->CurrentRenderer->AddActor(actor);

		this->Interactor->Render();

		vtkInteractorStyleTrackballCamera::OnLeftButtonUp();

		theParent_->UpdateExportContextMenu();
	}
}

void AutLib::TonbInteractorStyle::OnLeftButtonDown()
{
	int pickPosition[2];
	this->GetInteractor()->GetEventPosition(pickPosition);

	this->PreviousPosition[0] = pickPosition[0];
	this->PreviousPosition[1] = pickPosition[1];

	// Forward events
	vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}

void AutLib::TonbInteractorStyle::OnMouseWheelForward()
{
	vtkInteractorStyleTrackballCamera::OnMouseWheelForward();
}

void AutLib::TonbInteractorStyle::OnMouseWheelBackward()
{
	vtkInteractorStyleTrackballCamera::OnMouseWheelBackward();
}

void AutLib::TonbInteractorStyle::OnMiddleButtonDown()
{}

void AutLib::TonbInteractorStyle::OnRightButtonDown()
{
	int pickPosition[2];
	this->GetInteractor()->GetEventPosition(pickPosition);

	this->PreviousPosition[0] = pickPosition[0];
	this->PreviousPosition[1] = pickPosition[1];

	// Forward events
	vtkInteractorStyleTrackballCamera::OnMiddleButtonDown();
}

void AutLib::TonbInteractorStyle::OnRightButtonUp()
{
	int pickPosition[2];
	this->GetInteractor()->GetEventPosition(pickPosition);

	int xdist = pickPosition[0] - this->PreviousPosition[0];
	int ydist = pickPosition[1] - this->PreviousPosition[1];
	int moveDistance = (int)sqrt((double)(xdist*xdist + ydist * ydist));

	if (moveDistance > this->ResetPixelDistance)
	{
		vtkInteractorStyleTrackballCamera::OnMiddleButtonUp();
	}

	else
	{
		emit theParent_->customContextMenuRequested(QPoint(pickPosition[0], this->CurrentRenderer->GetRenderWindow()->GetSize()[1] - pickPosition[1]));

		vtkInteractorStyleTrackballCamera::OnMiddleButtonUp();
	}
}

void AutLib::TonbInteractorStyle::OnChar()
{
	// Get the keypress
	vtkRenderWindowInteractor *rwi = this->Interactor;
	std::string key = rwi->GetKeySym();

	// Output the key that was pressed
	std::cout << "Pressed " << key << std::endl;

	// Handle an arrow key
	if (key == "Up")
	{
		std::cout << "The up arrow was pressed." << std::endl;
	}

	// Handle w key
	if (key == "w" || key == "W")
	{
		vtkRenderWindowInteractor *rwi = this->Interactor;
		vtkActorCollection *ac;
		vtkActor *anActor, *aPart;
		vtkAssemblyPath *path;
		this->FindPokedRenderer(rwi->GetEventPosition()[0],
			rwi->GetEventPosition()[1]);
		if (this->CurrentRenderer != nullptr)
		{
			ac = this->CurrentRenderer->GetActors();
			vtkCollectionSimpleIterator ait;
			for (ac->InitTraversal(ait); (anActor = ac->GetNextActor(ait)); )
			{
				for (anActor->InitPathTraversal(); (path = anActor->GetNextPath()); )
				{
					aPart = static_cast<vtkActor *>(path->GetLastNode()->GetViewProp());
					//aPart->GetProperty()->SetEdgeColor(0, 0, 0);
					aPart->GetProperty()->EdgeVisibilityOn();
				}
			}
		}
		else
		{
			vtkWarningMacro(<< "no current renderer on the interactor style.");
		}
		rwi->Render();
	}

	if (key == "s" || key == "S")
	{
		vtkRenderWindowInteractor *rwi = this->Interactor;
		vtkActorCollection *ac;
		vtkActor *anActor, *aPart;
		vtkAssemblyPath *path;
		this->FindPokedRenderer(rwi->GetEventPosition()[0],
			rwi->GetEventPosition()[1]);
		if (this->CurrentRenderer != nullptr)
		{
			ac = this->CurrentRenderer->GetActors();
			vtkCollectionSimpleIterator ait;
			for (ac->InitTraversal(ait); (anActor = ac->GetNextActor(ait)); )
			{
				for (anActor->InitPathTraversal(); (path = anActor->GetNextPath()); )
				{
					aPart = static_cast<vtkActor *>(path->GetLastNode()->GetViewProp());
					//aPart->GetProperty()->SetEdgeColor(0, 0, 0);
					aPart->GetProperty()->EdgeVisibilityOff();
				}
			}
		}
		else
		{
			vtkWarningMacro(<< "no current renderer on the interactor style.");
		}
		rwi->Render();
	}

	// Forward events
	//vtkInteractorStyleTrackballCamera::OnKeyPress();
}