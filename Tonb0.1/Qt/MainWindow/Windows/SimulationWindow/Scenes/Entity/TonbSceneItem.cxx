#include <TonbSceneItem.hxx>

#include <QtWidgets/qapplication.h>

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
#include <vtkProperty.h>
#include <vtkRendererCollection.h>

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
		vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
		if (this->CurrentRenderer == nullptr)
		{
			return;
		}
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

};

vtkStandardNewMacro(customMouseInteractorStyle);

AutLib::TonbSceneItem::TonbSceneItem(SimulationWindow * parentwindow, TonbSimulationTreeWidget * parent, const QString & title)
	//: TonbTreeWidgetItem(parentwindow, parent, title)
	: QVTKOpenGLNativeWidget((QWidget*)parentwindow)
{
	double angle = 0;
	double r1, r2;
	double centerX, centerY;
	r1 = 50;
	r2 = 30;
	centerX = 10.0;
	centerY = 5.0;

	vtkSmartPointer<vtkPoints> points =
		vtkSmartPointer<vtkPoints>::New();
	int id = 0;
	while (angle <= 2.0 * vtkMath::Pi())
	{
		points->InsertNextPoint(r1 * sin(angle)*cos(angle) + centerX,
			r2 * sin(angle) + centerY,
			0.0);
		angle = angle + (vtkMath::Pi() / 600.0);
		++id;
	}

	vtkSmartPointer<vtkPolyLine> line =
		vtkSmartPointer<vtkPolyLine>::New();
	line->GetPointIds()->SetNumberOfIds(id);
	for (unsigned int i = 0; i < static_cast<unsigned int>(id); ++i)
	{
		line->GetPointIds()->SetId(i, i);
	}

	vtkSmartPointer<vtkCellArray> lines =
		vtkSmartPointer<vtkCellArray>::New();
	lines->InsertNextCell(line);

	vtkSmartPointer<vtkPolyData> polyData =
		vtkSmartPointer<vtkPolyData>::New();
	polyData->SetPoints(points);
	polyData->SetLines(lines);

	vtkSmartPointer<vtkLinearExtrusionFilter> extrude =
		vtkSmartPointer<vtkLinearExtrusionFilter>::New();
	extrude->SetInputData(polyData);
	extrude->SetExtrusionTypeToNormalExtrusion();
	extrude->SetVector(0, 0, 100.0);
	extrude->Update();

	vtkSmartPointer<vtkPolyDataMapper> lineMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	lineMapper->SetInputData(polyData);

	vtkSmartPointer<vtkActor> lineActor =
		vtkSmartPointer<vtkActor>::New();
	lineActor->SetMapper(lineMapper);

	vtkNew<vtkNamedColors> colors;

	lineActor->GetProperty()->SetColor(0.2, 0.6314, 0.788); // (Peacock) Color

	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(extrude->GetOutputPort());

	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->SetColor(0.753, 0.753, 0.753); // (Silver) Color

	/* =================================================================================================================== */

	theRenderer_ = vtkSmartPointer<vtkRenderer>::New();
	theRenderer_->SetBackground(0.862, 0.862, 0.862); // (Gainsboro) Color
	theRenderer_->AddActor(actor);
	theRenderer_->AddActor(lineActor);

	theRenderWindow_= vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();

	theRenderWindow_->AddRenderer(theRenderer_);

	theRenderWindowInteractor_= vtkSmartPointer<vtkRenderWindowInteractor>::New();
	theRenderWindowInteractor_->SetRenderWindow(theRenderWindow_);

	theInteractorStyle_= vtkSmartPointer<customMouseInteractorStyle>::New();

	theRenderWindowInteractor_->SetInteractorStyle(theInteractorStyle_);
	theRenderWindow_->SetInteractor(theRenderWindowInteractor_);

	theCamera_= vtkSmartPointer<vtkCamera>::New();
	theCamera_->SetPosition(0, 1, 0);
	theCamera_->SetFocalPoint(0, 0, 0);
	theCamera_->SetViewUp(0, 0, 1);
	theCamera_->Azimuth(30);
	theCamera_->Elevation(30);

	theRenderer_->SetActiveCamera(theCamera_);
	theRenderer_->ResetCamera();
	theRenderer_->ResetCameraClippingRange();

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

	this->GetRenderWindow()->AddRenderer(theRenderer_);
	//this->StartRenderWindowInteractor();
	//this->show();
}

void AutLib::TonbSceneItem::RenderTheRenderWindow()
{
	theRenderWindow_->Render();
}

void AutLib::TonbSceneItem::StartRenderWindowInteractor()
{
	theRenderWindowInteractor_->Start();
}

void AutLib::TonbSceneItem::StartScene()
{
	RenderTheRenderWindow();

	StartRenderWindowInteractor();
}