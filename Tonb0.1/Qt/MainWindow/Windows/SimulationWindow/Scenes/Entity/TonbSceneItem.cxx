#include <TonbSceneItem.hxx>
#include <TonbSimulationTreeWidget.hxx>
#include <TonbPartTreeWidgetItem.hxx>
#include <TonbDisplacementTreeWidgetItem.hxx>
#include <SimulationWindow.hxx>
#include <MainWindow.hxx>

//#include <Vessels_DispNo1.hxx>
//#include <Model_Entity.hxx>
#include <TopoDS.hxx>
#include <TopExp_Explorer.hxx>
#include <BRep_Tool.hxx>
#include <array>
#include <vtkPoints.h>
#include <vtkFloatArray.h>
#include <vtkCellArray.h>
#include <vtkPointData.h>

#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkObjectFactory.h>
#include <vtkRenderer.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkRenderWindow.h>
#include <vtkCamera.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>

#include <vtkPoints.h>
#include <vtkPolyLine.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkLinearExtrusionFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkAxesActor.h>
#include <vtkProperty.h>
#include <vtkRendererCollection.h>
#include <vtkAbstractPicker.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkPropAssembly.h>
#include <vtkAssemblyPath.h>

#include <vtkAutoInit.h>

VTK_MODULE_INIT(vtkRenderingContextOpenGL2)
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)
VTK_MODULE_INIT(vtkRenderingFreeType)

class customMouseInteractorStyle : public vtkInteractorStyleTrackballCamera
{

public:
	static customMouseInteractorStyle* New();

	vtkTypeMacro(customMouseInteractorStyle, vtkInteractorStyleTrackballCamera);

	virtual void OnLeftButtonDown()
	{
		// Forward events
		vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
		if (this->CurrentRenderer == nullptr)
		{
			return;
		}

	}

	virtual void OnMouseWheelForward()
	{
		vtkInteractorStyleTrackballCamera::OnMouseWheelForward();
	}

	virtual void OnMouseWheelBackward()
	{
		vtkInteractorStyleTrackballCamera::OnMouseWheelBackward();
	}

	virtual void OnMiddleButtonDown()
	{
	}

	virtual void OnRightButtonDown()
	{
		vtkInteractorStyleTrackballCamera::OnMiddleButtonDown();
	}

	virtual void OnRightButtonUp()
	{
		vtkInteractorStyleTrackballCamera::OnMiddleButtonUp();
	}

	virtual void OnChar()
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


};

vtkStandardNewMacro(customMouseInteractorStyle);

AutLib::TonbSceneItem::TonbSceneItem(SimulationWindow * parentwindow, TonbTreeWidgetItem * parent, const QString & title)
	: TonbTreeWidgetItem(parentwindow, parent, title)
	, QVTKOpenGLNativeWidget((QWidget*)parentwindow)
{
	setIcon(0, QIcon(":/Images/Icons/Scenes/Geometry_Scene_Icon.png"));
}

void AutLib::TonbSceneItem::StartScene()
{
	this->CreateMenu();

	this->CreateGeometry();

	theRenderer_ = vtkSmartPointer<vtkRenderer>::New();
	theRenderer_->SetBackground(0.862, 0.862, 0.862); // (Gainsboro) Color

	vtkSmartPointer<vtkProperty> bprop =
		vtkSmartPointer<vtkProperty>::New();
	bprop->SetColor(0.862, 0.862, 0.862);

	for (int i = 0; i < theGeometry_.size(); i++)
	{
		theRenderer_->AddActor(theGeometry_.at(i));
		theGeometry_.at(i)->GetProperty()->SetColor(0.753, 0.753, 0.753);
		//theGeometry_.at(i)->GetProperty()->SetOpacity(0.6);
		theGeometry_.at(i)->SetBackfaceProperty(bprop);
	}

	theRenderWindow_ = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();

	theRenderWindow_->AddRenderer(theRenderer_);

	theRenderWindowInteractor_ = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	theRenderWindowInteractor_->SetRenderWindow(theRenderWindow_);

	theInteractorStyle_ = vtkSmartPointer<customMouseInteractorStyle>::New();

	theRenderWindowInteractor_->SetInteractorStyle(theInteractorStyle_);

	vtkSmartPointer<vtkAxesActor> axes =
		vtkSmartPointer<vtkAxesActor>::New();

	vtkSmartPointer<vtkOrientationMarkerWidget> widget =
		vtkSmartPointer<vtkOrientationMarkerWidget>::New();

	widget->SetOutlineColor(0.9300, 0.5700, 0.1300);
	widget->SetOrientationMarker(axes);
	widget->SetInteractor(theRenderWindowInteractor_);
	widget->SetViewport(0.0, 0.0, 0.4, 0.4);
	widget->SetEnabled(1);
	widget->InteractiveOn();

	// Create a TextActor
	vtkSmartPointer<vtkTextActor> text = vtkSmartPointer<vtkTextActor>::New();
	text->SetInput("Test++");
	vtkTextProperty* tprop = text->GetTextProperty();
	tprop->SetFontFamilyToArial();
	tprop->ShadowOff();

	tprop->SetLineSpacing(1.0);
	tprop->SetFontSize(24);
	tprop->SetFontFamilyToArial();
	tprop->SetColor(0, 0, 0); // (Black) Color

	text->SetDisplayPosition(20, 20);
	theRenderer_->AddActor2D(text);

	theCamera_ = vtkSmartPointer<vtkCamera>::New();
	theCamera_->SetPosition(0, 1, 0);
	theCamera_->SetFocalPoint(0, 0, 0);
	theCamera_->SetViewUp(0, 0, 1);
	theCamera_->Azimuth(-180);
	//theCamera_->Elevation(30);

	theRenderer_->SetActiveCamera(theCamera_);
	theRenderer_->ResetCamera();
	theRenderer_->ResetCameraClippingRange();

	this->SetRenderWindow(theRenderWindow_);

	this->show();

	theRenderWindow_->Render();
	theRenderWindowInteractor_->Initialize();

	GetParentWindow()->GetParentWindow()->setCentralWidget(this);
}

AutLib::TonbPartTreeWidgetItem * AutLib::TonbSceneItem::GetPart(const QString & partName) const
{
	for (int i = 0; i < theParts_.size(); i++)
		if (theParts_.at(i)->text(0) == partName)
			return theParts_.at(i);
}

void AutLib::TonbSceneItem::AddPart(TonbPartTreeWidgetItem * part)
{
	theParts_.push_back(part);
}

void AutLib::TonbSceneItem::SetOpacitySlot(int value)
{
	/*theGeometry_->GetProperty()->SetOpacity((double)value / (double)100.0);
	this->GetRenderWindow()->Render();*/
}

void AutLib::TonbSceneItem::CreateMenu()
{
	setFlags(flags() | Qt::ItemIsEditable);

	theContextMenu_ = new SceneContextMenu;

	theContextMenu_->theRenameAction_ = new QAction("Rename", (QWidget*)this->GetParentWindow());

	GetContextMenu()->addAction(theContextMenu_->theRenameAction_);

	QObject::connect(theContextMenu_->theRenameAction_, SIGNAL(triggered()), this, SLOT(RenameItemSlot()));
}

void AutLib::TonbSceneItem::CreateGeometry()
{
	theParts_.at(0)->GetDisplacementGeometry()->DiscreteHull();
	theParts_.at(0)->GetDisplacementGeometry()->GetHullEntity();

	for (TopExp_Explorer Explorer(theParts_.at(0)->GetDisplacementGeometry()->GetHullEntity(), TopAbs_FACE); Explorer.More(); Explorer.Next())
	{
		vtkNew<vtkPolyData> Hull;
		vtkNew<vtkPoints> points;
		vtkNew<vtkCellArray> polys;

		TopLoc_Location Loc;
		Handle(Poly_Triangulation) Triangulation =
			BRep_Tool::Triangulation(TopoDS::Face(Explorer.Current()), Loc);

		if (Triangulation.IsNull()) continue;

		int nbNodes = Triangulation->Nodes().Size();
		int nbElements = Triangulation->Triangles().Size();
		//vtkNew<vtkFloatArray> scalars;

		for (auto i = 0ul; i < nbNodes; ++i)
		{
			points->InsertPoint(i, Triangulation->Nodes().Value(i + 1).X(), Triangulation->Nodes().Value(i + 1).Y(), Triangulation->Nodes().Value(i + 1).Z());
			//scalars->InsertTuple1(i, i);
		}

		for (int i = 0; i < nbElements; i++)
		{
			int I1, I2, I3;
			Triangulation->Triangles().Value(i + 1).Get(I1, I2, I3);
			std::array<std::array<vtkIdType, 3>, 1> order = { { {I1 - 1,I2 - 1,I3 - 1 } } };
			polys->InsertNextCell(vtkIdType(3), order[0].data());
		}
		Hull->SetPoints(points);
		Hull->SetPolys(polys);
		//cube->GetPointData()->SetScalars(scalars);

		// Now we'll look at it.
		vtkNew<vtkPolyDataMapper> HullMapper;
		HullMapper->SetInputData(Hull);
		//HullMapper->SetScalarRange(cube->GetScalarRange());
		theGeometry_.push_back(vtkSmartPointer<vtkActor>::New());
		theGeometry_.at(theGeometry_.size() - 1)->SetMapper(HullMapper);
		theGeometry_.at(theGeometry_.size() - 1)->GetProperty()->SetEdgeColor(0, 0, 0);
		//theGeometry_.at(theGeometry_.size() - 1)->GetProperty()->EdgeVisibilityOn();
		//theGeometry_ = vtkSmartPointer<vtkActor>::New();
		//theGeometry_->SetMapper(HullMapper);
	}

}

void AutLib::TonbSceneItem::RenameItemSlot()
{
	GetParentView()->editItem(this);
}