#include <TonbSceneItem.hxx>
#include <TonbSimulationTreeWidget.hxx>
#include <TonbPartTWI.hxx>
#include <TonbDisplacementTWI.hxx>
#include <SimulationWindow.hxx>
#include <MainWindow.hxx>

#include <Vessels_DispNo1.hxx>
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
#include <vtkPropPicker.h>
#include <vtkSphereSource.h>

#include <vtkWindowToImageFilter.h>
#include <vtkVersion.h>
#include <vtkJPEGWriter.h>

#include <qtvariantproperty.h>
#include <qttreepropertybrowser.h>
#include <qtpropertybrowser.h>

#include <Cad3d_Solid.hxx>
#include <Solid_Paired.hxx>
#include <Solid_Edge.hxx>
#include <Solid_Vertex.hxx>
#include <TopoDS_Edge.hxx>
#include <Solid_Curve.hxx>

#include <vtkParametricSpline.h>
#include <vtkParametricFunctionSource.h>

#include <TonbSceneTabWidget.hxx>

#include <vtkAutoInit.h>

QColor GeometryColorRGB(0.753 * 255, 0.753 * 255, 0.753 * 255);
QColor GeometrySelectedColorRGB(1.0 * 255, 0.0 * 255, 1.0 * 255);

VTK_MODULE_INIT(vtkRenderingContextOpenGL2)
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)
VTK_MODULE_INIT(vtkRenderingFreeType)

class customMouseInteractorStyle : public vtkInteractorStyleTrackballCamera
{

private:

	QList<vtkActor*> theSelectedActors_;

	QList<vtkActor*> theHiddenActors_;

	AutLib::TonbSceneItem* theParent_ = nullptr;

	int PreviousPosition[2];
	int ResetPixelDistance;

public:
	static customMouseInteractorStyle* New();

	vtkTypeMacro(customMouseInteractorStyle, vtkInteractorStyleTrackballCamera);

	customMouseInteractorStyle() : ResetPixelDistance(5)
	{
		this->PreviousPosition[0] = 0;
		this->PreviousPosition[1] = 0;
	}

	void SetParent(AutLib::TonbSceneItem* parent)
	{
		theParent_ = parent;
	}

	void SetSelectedActorColor(QColor color)
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

	void AddActorToSelectedActors(vtkActor* actor)
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

	void HideSelectedActors()
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

	void ShowAllActors()
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

	virtual void OnLeftButtonUp() override
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

				if(this->Interactor->GetControlKey())
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

	virtual void OnLeftButtonDown() override
	{
		int pickPosition[2];
		this->GetInteractor()->GetEventPosition(pickPosition);

		this->PreviousPosition[0] = pickPosition[0];
		this->PreviousPosition[1] = pickPosition[1];

		// Forward events
		vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
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
		int pickPosition[2];
		this->GetInteractor()->GetEventPosition(pickPosition);

		this->PreviousPosition[0] = pickPosition[0];
		this->PreviousPosition[1] = pickPosition[1];

		// Forward events
		vtkInteractorStyleTrackballCamera::OnMiddleButtonDown();
	}

	virtual void OnRightButtonUp()
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

	QList<vtkActor*> GetSelectedActors() const
	{
		return theSelectedActors_;
	}

	QList<vtkActor*>& GetSelectedActors()
	{
		return theSelectedActors_;
	}
};

vtkStandardNewMacro(customMouseInteractorStyle);

AutLib::TonbSceneItem::TonbSceneItem
(
	SimulationWindow* parentwindow,
	TonbTWI* parent,
	const QString & title
)
	: TonbTWI(parentwindow, parent, title)
	, QVTKOpenGLNativeWidget((QWidget*)parentwindow)
{
	setIcon(0, QIcon(":/Images/Icons/Scenes/Geometry_Scene_Icon.png"));

	QObject::connect((QWidget*)this,
		SIGNAL(customContextMenuRequested(const QPoint&)),
		(TonbTWI*)this,
		SLOT(onCustomContextMenuRequested(const QPoint&)));

	QObject::connect
	(
		this->GetParentView(),
		SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)),
		(TonbTWI*)this,
		SLOT(onDoubleClickSlot(QTreeWidgetItem*, int))
	);

	QtVariantProperty* item;
	item = this->GetVariantPropertyManager()->addProperty(QVariant::Color, QLatin1String("Face Color"));
	item->setValue(QColor(GeometryColorRGB.red(), GeometryColorRGB.green(), GeometryColorRGB.blue()));
	item->setPropertyId("Face Color");
	this->GetProperty()->addProperty(item);
	//this->GetVariantPropertyManager()->addProperty(item);
}

void AutLib::TonbSceneItem::StartScene()
{
	this->CreateMenu();

	this->CreateGeometry();

	this->FindProperty("Name")->property()->setEnabled(true);

	theRenderer_ = vtkSmartPointer<vtkRenderer>::New();
	theRenderer_->SetBackground(0.862, 0.862, 0.862); // (Gainsboro) Color

	vtkSmartPointer<vtkProperty> bprop =
		vtkSmartPointer<vtkProperty>::New();
	bprop->SetColor(GeometryColorRGB.redF(), GeometryColorRGB.greenF(), GeometryColorRGB.blueF());

	for (int i = 0; i < theGeometry_.size(); i++)
	{
		theRenderer_->AddActor(theGeometry_.at(i));
		theGeometry_.at(i)->GetProperty()->SetColor(GeometryColorRGB.redF(), GeometryColorRGB.greenF(), GeometryColorRGB.blueF());
		//theGeometry_.at(i)->GetProperty()->SetColor(0.2, 0.6314, 0.788);
		//theGeometry_.at(i)->GetProperty()->SetOpacity(0.6);
		theGeometry_.at(i)->SetBackfaceProperty(bprop);
	}

	theRenderWindow_ = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();

	theRenderWindow_->AddRenderer(theRenderer_);

	theRenderWindowInteractor_ = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	theRenderWindowInteractor_->SetRenderWindow(theRenderWindow_);

	theInteractorStyle_ = vtkSmartPointer<customMouseInteractorStyle>::New();

	theInteractorStyle_->SetParent(this);

	theInteractorStyle_->SetMouseWheelMotionFactor(0.5);

	theRenderWindowInteractor_->SetInteractorStyle(theInteractorStyle_);

	/*vtkSmartPointer<vtkAxesActor> axes =
		vtkSmartPointer<vtkAxesActor>::New();

	vtkSmartPointer<vtkOrientationMarkerWidget> widget =
		vtkSmartPointer<vtkOrientationMarkerWidget>::New();

	widget->SetOutlineColor(0.9300, 0.5700, 0.1300);
	widget->SetOrientationMarker(axes);
	widget->SetInteractor(theRenderWindowInteractor_);
	widget->SetViewport(0.0, 0.0, 0.4, 0.4);
	widget->SetEnabled(1);
	widget->InteractiveOn();*/

	// Create a TextActor
	theLogoActor_ = vtkSmartPointer<vtkTextActor>::New();
	theLogoActor_->SetInput("Tonb++");
	vtkTextProperty* tprop = theLogoActor_->GetTextProperty();
	tprop->SetFontFamilyToArial();
	tprop->ShadowOff();

	tprop->SetLineSpacing(1.0);
	tprop->SetFontSize(24);
	tprop->SetFontFamilyToArial();
	tprop->ShadowOn();
	tprop->SetColor(0, 0, 0); // (Black) Color

	theLogoActor_->SetDisplayPosition(20, 20);
	theRenderer_->AddActor2D(theLogoActor_);

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

	if (!GetParentWindow()->GetSceneTabWidget())
		GetParentWindow()->GetSceneTabWidget() = std::make_shared<TonbSceneTabWidget>(GetParentWindow(), (TonbTWI*)this, this->text(0));

	GetParentWindow()->GetSceneTabWidget()->addTab((QWidget*)this, this->text(0));
	GetParentWindow()->GetSceneTabWidget()->setCurrentWidget((QWidget*)this);

	GetParentWindow()->GetParentWindow()->setCentralWidget((QWidget*)(GetParentWindow()->GetSceneTabWidget().get()));
}

void AutLib::TonbSceneItem::SnapshotSlot()
{
	// Screenshot  
	vtkSmartPointer<vtkWindowToImageFilter> windowToImageFilter =
		vtkSmartPointer<vtkWindowToImageFilter>::New();
	windowToImageFilter->SetInput(theRenderWindow_);

	int Magnification = 2;

	//windowToImageFilter->SetScale(1366 / theRenderWindow_->GetSize()[0], 768 / theRenderWindow_->GetSize()[1]); // image quality
	windowToImageFilter->SetScale(Magnification); // image quality

	theLogoActor_->GetTextProperty()->SetFontSize(Magnification*theLogoActor_->GetTextProperty()->GetFontSize());
	theLogoActor_->GetTextProperty()->SetShadowOffset
	(
		Magnification*theLogoActor_->GetTextProperty()->GetShadowOffset()[0],
		Magnification*theLogoActor_->GetTextProperty()->GetShadowOffset()[1]
	);

	/*for (int i = 0; i < theGeometry_.size(); i++)
		theGeometry_[i]->GetProperty()->SetLineWidth((float)Magnification*theGeometry_[i]->GetProperty()->GetLineWidth());*/

	windowToImageFilter->ReadFrontBufferOff(); // read from the back buffer
	windowToImageFilter->Update();

	vtkSmartPointer<vtkJPEGWriter> writer =
		vtkSmartPointer<vtkJPEGWriter>::New();
	writer->SetFileName("screenshot.jpeg");
	writer->SetInputConnection(windowToImageFilter->GetOutputPort());
	writer->SetQuality(100);
	writer->Write();

	theLogoActor_->GetTextProperty()->SetFontSize((1.0 / (float)Magnification)*theLogoActor_->GetTextProperty()->GetFontSize());
	theLogoActor_->GetTextProperty()->SetShadowOffset
	(
		(1.0 / (float)Magnification)*theLogoActor_->GetTextProperty()->GetShadowOffset()[0],
		(1.0 / (float)Magnification)*theLogoActor_->GetTextProperty()->GetShadowOffset()[1]
	);

	/*for (int i = 0; i < theGeometry_.size(); i++)
		theGeometry_[i]->GetProperty()->SetLineWidth((1.0 / (float)Magnification)*theGeometry_[i]->GetProperty()->GetLineWidth());*/

	theRenderWindow_->Render();
}

void AutLib::TonbSceneItem::onCustomContextMenuRequested(const QPoint & pos)
{
	theSceneContextMenu_->theSeneMenu_->exec(this->mapToGlobal(pos));
}

void AutLib::TonbSceneItem::HideObjectSlot()
{
	if (theInteractorStyle_->GetSelectedActors().size() == 0)
		return;
	else
	{
		theInteractorStyle_->HideSelectedActors();
		if(!theSceneContextMenu_->theShowAllAction_->isEnabled())
			theSceneContextMenu_->theShowAllAction_->setEnabled(true);
	}
}

void AutLib::TonbSceneItem::ShowAllObjectSlot()
{
	theInteractorStyle_->ShowAllActors();
	theSceneContextMenu_->theShowAllAction_->setEnabled(false);
}

void AutLib::TonbSceneItem::UpdateGeometryColorSlot(QtProperty * property, const QVariant & val)
{
	//std::cout << property->valueText().toStdString() << "   " << val.toString().toStdString() << std::endl;
	QColor c(val.value<QColor>());

	GeometryColorRGB = c;

	for (int i = 0; i < theGeometry_.size(); i++)
	{
		theGeometry_.at(i)->GetProperty()->SetColor(c.redF(), c.greenF(), c.blueF());
		vtkSmartPointer<vtkProperty> bprop =
			vtkSmartPointer<vtkProperty>::New();
		bprop->SetColor(c.redF(), c.greenF(), c.blueF());
		bprop->SetOpacity(c.alphaF());
		theGeometry_.at(i)->SetBackfaceProperty(bprop);

		theGeometry_.at(i)->GetProperty()->SetOpacity(c.alphaF());
	}
	if(theRenderWindowInteractor_)
		theRenderWindowInteractor_->Render();
}

void AutLib::TonbSceneItem::onDoubleClickSlot(QTreeWidgetItem * item, int col)
{
	if(item->text(col) == this->text(col))
		GetParentWindow()->GetSceneTabWidget()->setCurrentIndex(GetParentWindow()->GetSceneTabWidget()->indexOf((QWidget*)this));
}

std::shared_ptr<AutLib::TonbPartTWI> AutLib::TonbSceneItem::GetPart(const QString & partName) const
{
	for (int i = 0; i < theParts_.size(); i++)
		if (theParts_.at(i)->text(0) == partName)
			return theParts_.at(i);
}

void AutLib::TonbSceneItem::AddPart(std::shared_ptr<TonbPartTWI> part)
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
	//setFlags(flags() | Qt::ItemIsEditable);

	theSceneItemContextMenu_ = std::make_shared<SceneItemContextMenu>();

	theSceneItemContextMenu_->theRenameAction_ = new QAction("Rename", (QWidget*)this->GetParentWindow());
	theSceneItemContextMenu_->theExportSceneAction_ = new QAction("Export", (QWidget*)this->GetParentWindow());
	theSceneItemContextMenu_->theSnapshotAction_ = new QAction("Snapshot", (QWidget*)this->GetParentWindow());
	theSceneItemContextMenu_->theExportSceneAction_->setEnabled(false);

	GetContextMenu()->addAction(theSceneItemContextMenu_->theRenameAction_);
	GetContextMenu()->addAction(theSceneItemContextMenu_->theExportSceneAction_);
	GetContextMenu()->addAction(theSceneItemContextMenu_->theSnapshotAction_);

	QObject::connect(theSceneItemContextMenu_->theRenameAction_, SIGNAL(triggered()), (TonbTWI*)this, SLOT(RenameItemSlot()));
	QObject::connect(theSceneItemContextMenu_->theExportSceneAction_, SIGNAL(triggered()), (TonbTWI*)this, SLOT(ExportScene()));
	QObject::connect(theSceneItemContextMenu_->theSnapshotAction_, SIGNAL(triggered()), (TonbTWI*)this, SLOT(SnapshotSlot()));

	theSceneContextMenu_ = std::make_shared <SceneContextMenu>(this);
	theSceneContextMenu_->theSeneMenu_->addAction(theSceneItemContextMenu_->theExportSceneAction_);
	theSceneContextMenu_->theSeneMenu_->addAction(theSceneItemContextMenu_->theSnapshotAction_);
	theSceneContextMenu_->theHideAction_ = new QAction("Hide", theSceneContextMenu_->theSeneMenu_);
	theSceneContextMenu_->theHideAction_->setEnabled(false);
	theSceneContextMenu_->theShowAllAction_ = new QAction("Show All", theSceneContextMenu_->theSeneMenu_);
	theSceneContextMenu_->theShowAllAction_->setEnabled(false);
	theSceneContextMenu_->theSeneMenu_->addAction(theSceneContextMenu_->theHideAction_);
	theSceneContextMenu_->theSeneMenu_->addAction(theSceneContextMenu_->theShowAllAction_);

	QObject::connect(theSceneContextMenu_->theHideAction_, SIGNAL(triggered()), (TonbTWI*)this, SLOT(HideObjectSlot()));
	QObject::connect(theSceneContextMenu_->theShowAllAction_, SIGNAL(triggered()), (TonbTWI*)this, SLOT(ShowAllObjectSlot()));
}

void AutLib::TonbSceneItem::CreateGeometry()
{
	//theParts_.at(0)->GetDisplacementGeometry()->DiscreteHull();
	/*if(std::dynamic_pointer_cast<DispNo1_HullPatch>(theParts_.at(0)->GetPartGeometry()->thePartEntity_) ||
		std::dynamic_pointer_cast<DispNo1_BareHull>(theParts_.at(0)->GetPartGeometry()->thePartEntity_))
		theParts_.at(0)->GetPartGeometry()->thePartEntity_->Discrete();*/
	
	/*std::vector<std::shared_ptr<Solid_Entity>> entities;
	theParts_.at(0)->GetPartGeometry()->thePartSolid_->Edges()->RetrieveTo(entities);*/

	//theParts_.at(0)->GetDisplacementGeometry()->GetHullEntity();

	for (int i = 0; i < theParts_.at(0)->GetPartGeometry()->theEdges_.size(); i++)
	{
		auto edge = std::dynamic_pointer_cast<Solid_Paired>(theParts_.at(0)->GetPartGeometry()->theEdges_.at(i)->theData_);
		vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
		
		double u0 = edge->Edge0()->Geometry()->FirstParameter(), un = edge->Edge0()->Geometry()->LastParameter();
		int nu = 200;
		double du = (un - u0) / (double)nu;
		for (int j = 0; j <= nu; j++)
		{
			double u = j * du + u0;
			if (u < u0)
				u = u0;
			else if (u > un)
				u = un;
			double pt[3] = 
			{ 
				edge->Edge0()->Geometry()->Value(u).X(),
				edge->Edge0()->Geometry()->Value(u).Y(),
				edge->Edge0()->Geometry()->Value(u).Z() 
			};
			points->InsertNextPoint(pt);
		}

		/*double pt1[3] = { edge->Edge0()->End()->Coord().X() ,edge->Edge0()->End()->Coord().Y() ,edge->Edge0()->End()->Coord().Z() };
		double pt2[3] = { edge->Edge0()->Start()->Coord().X() ,edge->Edge0()->Start()->Coord().Y() ,edge->Edge0()->Start()->Coord().Z() };
		points->InsertNextPoint(pt1);
		points->InsertNextPoint(pt2);*/

		vtkSmartPointer<vtkParametricSpline> spline =
			vtkSmartPointer<vtkParametricSpline>::New();
		spline->SetPoints(points);

		vtkSmartPointer<vtkParametricFunctionSource> functionSource =
			vtkSmartPointer<vtkParametricFunctionSource>::New();
		functionSource->SetParametricFunction(spline);
		functionSource->Update();

		vtkNew<vtkPolyDataMapper> Mapper;
		Mapper->SetInputConnection(functionSource->GetOutputPort());

		theGeometry_.push_back(vtkSmartPointer<vtkActor>::New());
		theGeometry_.at(theGeometry_.size() - 1)->SetMapper(Mapper);
		theGeometry_.at(theGeometry_.size() - 1)->GetProperty()->SetEdgeColor(0, 0, 1.0);

		theParts_.at(0)->GetPartGeometry()->theEdges_.at(i)->thePointerToActor_ = theGeometry_.at(theGeometry_.size() - 1);
	}

	int it = 0;
	for 
		(
			TopExp_Explorer Explorer(theParts_.at(0)->GetPartGeometry()->thePartEntity_->GetEntity(), TopAbs_FACE);
			Explorer.More();
			Explorer.Next(), it++
		)
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
			//scalars->InsertTuple1(i, std::sin(i));
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
		//Hull->GetPointData()->SetScalars(scalars);

		// Now we'll look at it.
		vtkNew<vtkPolyDataMapper> HullMapper;
		HullMapper->SetInputData(Hull);
		//HullMapper->SetScalarRange(cube->GetScalarRange());
		theGeometry_.push_back(vtkSmartPointer<vtkActor>::New());
		theGeometry_.at(theGeometry_.size() - 1)->SetMapper(HullMapper);
		//theGeometry_.at(theGeometry_.size() - 1)->GetProperty()->SetEdgeColor(0, 0, 0);
		//theGeometry_.at(theGeometry_.size() - 1)->GetProperty()->EdgeVisibilityOn();
		//theGeometry_ = vtkSmartPointer<vtkActor>::New();
		//theGeometry_->SetMapper(HullMapper);

		theParts_.at(0)->GetPartGeometry()->theFaces_.at(it)->thePointerToActor_ = theGeometry_.at(theGeometry_.size() - 1);
	}

}

void AutLib::TonbSceneItem::UpdateExportContextMenu()
{
	if (theInteractorStyle_->GetSelectedActors().size() != 0)
	{
		//theSceneItemContextMenu_->theExportSceneAction_->setEnabled(true);
		theSceneContextMenu_->theHideAction_->setEnabled(true);
	}
	else
	{
		//theSceneItemContextMenu_->theExportSceneAction_->setEnabled(false);
		theSceneContextMenu_->theHideAction_->setEnabled(false);
	}
}

void AutLib::TonbSceneItem::AddActorToSelectedActors(vtkActor * actor)
{
	this->theInteractorStyle_->AddActorToSelectedActors(actor);
}

void AutLib::TonbSceneItem::SetSelectedActorColor(QColor color)
{
	theInteractorStyle_->SetSelectedActorColor(color);
}

//void AutLib::TonbSceneItem::RenameItemSlot()
//{
//	GetParentView()->editItem(this);
//}