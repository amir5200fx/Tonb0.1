#include <TonbPartFeaturesTWI.hxx>
#include <Model_Box.hxx>
#include <Model_Cone.hxx>
#include <Model_Cylinder.hxx>
#include <Model_Sphere.hxx>
#include <Model_Torus.hxx>
#include <Solid_Entity.hxx>
#include <Solid_Face.hxx>
#include <Solid_Paired.hxx>
#include <Vessels_DispNo1.hxx>
#include <Model_Entity.hxx>

#include <TonbPartTWI.hxx>
#include <TonbSimulationTreeWidget.hxx>
#include <TonbScenesTWI.hxx>
#include <TonbSceneItem.hxx>
#include <TonbInteractorStyle.hxx>

#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>

#include <memory>

#define AddFeaturesToPart(features, model, model_type, name)\
if (std::dynamic_pointer_cast<model_type>(model))\
{\
	for (int i = 0; i < features.size(); i++)\
	{\
		if (std::dynamic_pointer_cast<Solid_Face>(features.at(i)))\
			{\
				theFeaturesItem_.push_back\
				(\
					std::make_shared<TonbTWI>(parentwindow, this, TonbTWI::CorrectName(this, QString(name) + " Surface"))\
				);\
				((TonbPartTWI*)(GetParentItem()))->GetPartGeometry()->theFaces_.at(i)->thePointerToItem_ = theFeaturesItem_.at(theFeaturesItem_.size() - 1);\
			}\
		else if (std::dynamic_pointer_cast<Solid_Paired>(features.at(i)))\
			{\
				theFeaturesItem_.push_back\
				(\
					std::make_shared<TonbTWI>(parentwindow, this, TonbTWI::CorrectName(this, QString(name) + " Curve"))\
				);\
				((TonbPartTWI*)(GetParentItem()))->GetPartGeometry()->theEdges_.at(i)->thePointerToItem_ = theFeaturesItem_.at(theFeaturesItem_.size() - 1);\
			}\
	}\
}

AutLib::TonbPartFeaturesTWI::TonbPartFeaturesTWI
(
	SimulationWindow* parentwindow,
	TonbTWI* parent,
	const QString & title,
	QList<std::shared_ptr<Solid_Entity>> features,
	std::shared_ptr<Model_Entity> model
)
	: TonbTWI(parentwindow, parent, title)
	, theFeatures_(features)
{
	AddFeaturesToPart(theFeatures_, model, Model_Box, "Block");
	AddFeaturesToPart(theFeatures_, model, Model_Cone, "Cone");
	AddFeaturesToPart(theFeatures_, model, Model_Cylinder, "Cylinder");
	AddFeaturesToPart(theFeatures_, model, Model_Sphere, "Sphere");
	AddFeaturesToPart(theFeatures_, model, Model_Torus, "Torus");

	if (std::dynamic_pointer_cast<DispNo1_BareHull>(model))
	{
		AddFeaturesToPart(theFeatures_, model, DispNo1_BareHull, "BareHull");
		goto AA;
	}

	AddFeaturesToPart(theFeatures_, model, DispNo1_HullPatch, "HullPatch");
	AA:

	connect
	(
		GetParentView(),
		SIGNAL(itemClicked(QTreeWidgetItem *, int)),
		this,
		SLOT(SelectPartFeature(QTreeWidgetItem *, int))
	);

	for (int i = 0; i < theFeatures_.size(); i++)
	{

		if (std::dynamic_pointer_cast<Solid_Paired>(theFeatures_.at(i)))
			theFeaturesItem_.at(i)->setIcon(0, QIcon(":/part/Icons/Part/Features/Curve.png"));
		else if (std::dynamic_pointer_cast<Solid_Face>(theFeatures_.at(i)))
			theFeaturesItem_.at(i)->setIcon(0, QIcon(":/part/Icons/Part/Features/Surface.png"));
	}

	//std::cout << (((TonbPartTWI*)GetParentItem())->GetPartGeometry()->theEdges_.at(0)->thePointerToActor_) << std::endl;
}

void AutLib::TonbPartFeaturesTWI::SelectPartFeature(QTreeWidgetItem* item, int column)
{
	if (!(TonbPartFeaturesTWI*)item)
		return;

	if (std::dynamic_pointer_cast<Solid_Face>(theFeatures_.at(0)) && GetParentView()->GetScenesItem()->GetScenes().size() != 0)
	{
		for (int i = 0; i < ((TonbPartTWI*)(GetParentItem()))->GetPartGeometry()->theFaces_.size(); i++)
		{
			if (((TonbPartTWI*)(GetParentItem()))->GetPartGeometry()->theFaces_.at(i)->thePointerToItem_.get() == item)
			{
				//std::cout << "Surface selected\n";
				auto data = ((TonbPartTWI*)(GetParentItem()))->GetPartGeometry();
				/*data->theFaces_.at(i)->thePointerToActor_->GetProperty()->SetColor(1.0, 0.0, 1.0);
				data->theFaces_.at(i)->thePointerToActor_->GetBackfaceProperty()->SetColor(1.0, 0.0, 1.0);*/
				data->thePointerToScene_->SetSelectedActorColor(AutLib::TonbInteractorStyle::GeometryColorRGB);
				data->thePointerToScene_->GetInteractorStyle()->GetSelectedActors().clear();

				for (int j = 0; j < data->thePointerToScene_->GetGeometry().size(); j++)
				{
					if (data->thePointerToScene_->GetGeometry().at(j) != data->theFaces_.at(i)->thePointerToActor_)
					{
						double opacity = 0.5;
						data->thePointerToScene_->GetGeometry().at(j)->GetProperty()->SetOpacity(opacity);
						data->thePointerToScene_->GetGeometry().at(j)->GetBackfaceProperty()->SetOpacity(opacity);
					}
					else
					{
						double opacity = 1.0;
						data->thePointerToScene_->GetGeometry().at(j)->GetProperty()->SetOpacity(opacity);
						data->thePointerToScene_->GetGeometry().at(j)->GetBackfaceProperty()->SetOpacity(opacity);
					}
				}

				data->thePointerToScene_->AddActorToSelectedActors(data->theFaces_.at(i)->thePointerToActor_);
				data->thePointerToScene_->SetSelectedActorColor(QColor(255, 0, 255));
				data->thePointerToScene_->UpdateExportContextMenu();
				data->thePointerToScene_->GetRenderWindow()->Render();
				return;
			}
		}
	}
	else if (std::dynamic_pointer_cast<Solid_Paired>(theFeatures_.at(0)) && GetParentView()->GetScenesItem()->GetScenes().size() != 0)
	{
		for (int i = 0; i < ((TonbPartTWI*)(GetParentItem()))->GetPartGeometry()->theEdges_.size(); i++)
		{
			if (((TonbPartTWI*)(GetParentItem()))->GetPartGeometry()->theEdges_.at(i)->thePointerToItem_.get() == item)
			{
				//std::cout << "Curve selected\n";
				auto data = ((TonbPartTWI*)(GetParentItem()))->GetPartGeometry();
				/*data->theEdges_.at(i)->thePointerToActor_->GetProperty()->SetColor(1.0, 0.0, 1.0);
				data->theEdges_.at(i)->thePointerToActor_->GetBackfaceProperty()->SetColor(1.0, 0.0, 1.0);*/
				data->thePointerToScene_->SetSelectedActorColor(AutLib::TonbInteractorStyle::GeometryColorRGB);
				data->thePointerToScene_->GetInteractorStyle()->GetSelectedActors().clear();

				for (int j = 0; j < data->thePointerToScene_->GetGeometry().size(); j++)
				{
					double opacity = 0.5;
					data->thePointerToScene_->GetGeometry().at(j)->GetProperty()->SetOpacity(opacity);
					data->thePointerToScene_->GetGeometry().at(j)->GetBackfaceProperty()->SetOpacity(opacity);
				}

				data->theEdges_.at(i)->thePointerToActor_->GetProperty()->SetLineWidth(2.0);
				data->thePointerToScene_->AddActorToSelectedActors(data->theEdges_.at(i)->thePointerToActor_);
				data->thePointerToScene_->SetSelectedActorColor(QColor(255, 0, 255));
				data->thePointerToScene_->UpdateExportContextMenu();
				data->thePointerToScene_->GetRenderWindow()->Render();

				return;
			}
		}
	}
}