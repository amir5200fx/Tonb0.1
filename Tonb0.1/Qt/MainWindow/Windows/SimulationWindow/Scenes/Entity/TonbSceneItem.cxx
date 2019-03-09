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

	virtual void OnKeyPress()
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

		// Handle a "normal" key
		if (key == "a")
		{
			std::cout << "The a key was pressed." << std::endl;
		}

		// Forward events
		vtkInteractorStyleTrackballCamera::OnKeyPress();
	}


};

vtkStandardNewMacro(customMouseInteractorStyle);

AutLib::TonbSceneItem::TonbSceneItem(SimulationWindow * parentwindow, TonbTreeWidgetItem * parent, const QString & title)
	: TonbTreeWidgetItem(parentwindow, parent, title)
	, QVTKOpenGLNativeWidget((QWidget*)parentwindow)
{
	setIcon(0, QIcon(":/Images/Icons/Scenes/Geometry_Scene_Icon.png"));


	//double angle = 0;
	//double r1, r2;
	//double centerX, centerY;
	//r1 = 50;
	//r2 = 30;
	//centerX = 10.0;
	//centerY = 5.0;

	//vtkSmartPointer<vtkPoints> points =
	//	vtkSmartPointer<vtkPoints>::New();
	//int id = 0;
	//while (angle <= 2.0 * vtkMath::Pi())
	//{
	//	points->InsertNextPoint(r1 * sin(angle)*cos(angle) + centerX,
	//		r2 * sin(angle) + centerY,
	//		0.0);
	//	angle = angle + (vtkMath::Pi() / 600.0);
	//	++id;
	//}

	//vtkSmartPointer<vtkPolyLine> line =
	//	vtkSmartPointer<vtkPolyLine>::New();
	//line->GetPointIds()->SetNumberOfIds(id);
	//for (unsigned int i = 0; i < static_cast<unsigned int>(id); ++i)
	//{
	//	line->GetPointIds()->SetId(i, i);
	//}

	//vtkSmartPointer<vtkCellArray> lines =
	//	vtkSmartPointer<vtkCellArray>::New();
	//lines->InsertNextCell(line);

	//vtkSmartPointer<vtkPolyData> polyData =
	//	vtkSmartPointer<vtkPolyData>::New();
	//polyData->SetPoints(points);
	//polyData->SetLines(lines);

	//vtkSmartPointer<vtkLinearExtrusionFilter> extrude =
	//	vtkSmartPointer<vtkLinearExtrusionFilter>::New();
	//extrude->SetInputData(polyData);
	//extrude->SetExtrusionTypeToNormalExtrusion();
	//extrude->SetVector(0, 0, 100.0);
	//extrude->Update();

	//vtkSmartPointer<vtkPolyDataMapper> lineMapper =
	//	vtkSmartPointer<vtkPolyDataMapper>::New();
	//lineMapper->SetInputData(polyData);

	//vtkSmartPointer<vtkActor> lineActor =
	//	vtkSmartPointer<vtkActor>::New();
	//lineActor->SetMapper(lineMapper);

	//vtkNew<vtkNamedColors> colors;

	//lineActor->GetProperty()->SetColor(0.2, 0.6314, 0.788); // (Peacock) Color

	//vtkSmartPointer<vtkPolyDataMapper> mapper =
	//	vtkSmartPointer<vtkPolyDataMapper>::New();
	//mapper->SetInputConnection(extrude->GetOutputPort());

	//theGeometry_ =
	//	vtkSmartPointer<vtkActor>::New();
	//theGeometry_->SetMapper(mapper);
	//theGeometry_->GetProperty()->SetColor(0.753, 0.753, 0.753); // (Silver) Color

	/* =================================================================================================================== */
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
	//theRenderer_->AddActor(lineActor);

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
		//theGeometry_ = vtkSmartPointer<vtkActor>::New();
		//theGeometry_->SetMapper(HullMapper);
	}

}

void AutLib::TonbSceneItem::RenameItemSlot()
{
	GetParentView()->editItem(this);
}