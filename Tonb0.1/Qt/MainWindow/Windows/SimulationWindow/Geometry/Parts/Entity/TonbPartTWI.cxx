#include <TonbPartTWI.hxx>
#include <TonbSimulationTreeWidget.hxx>
#include <TonbScenesTWI.hxx>
#include <TonbSceneItem.hxx>
#include <qttreepropertybrowser.h>
#include <QtWidgets/qfiledialog.h>
#include <QtWidgets/qmessagebox.h>
#include <TonbDisplacementTWI.hxx>
#include <Cad3d_Solid.hxx>
#include <Model_Entity.hxx>
#include <Model_Box.hxx>
#include <Cad3d_SolidTools.hxx>

#include <Solid_Paired.hxx>
#include <Solid_Face.hxx>

#include <TonbPartFeaturesTWI.hxx>

AutLib::TonbPartTWI::TonbPartData::TonbPartData(std::shared_ptr<Solid_Entity> data)
	: theData_(data)
{
}

AutLib::TonbPartTWI::TonbPart::TonbPart(std::shared_ptr<Model_Entity> model, std::shared_ptr<TonbTWI> theParent)
	: thePartEntity_(model)
	, theParent_(theParent)
{
	thePartEntity_->Discrete();

	thePartSolid_ = std::make_shared<Cad3d_Solid>(Cad3d_SolidTools::GetSurfaces(model->GetEntity()));
	thePartSolid_->SetName(model->Name());

	std::vector<std::shared_ptr<Solid_Entity>> entitiesEdges;
	thePartSolid_->Edges()->RetrieveTo(entitiesEdges);

	for (const auto& x : entitiesEdges)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(std::dynamic_pointer_cast<Solid_Paired>(x));
		auto edge = std::dynamic_pointer_cast<Solid_Paired>(x);

		theEdges_.push_back(std::make_shared<TonbPartData>(edge));
	}

	std::vector<std::shared_ptr<Solid_Entity>> entitiesFaces;
	thePartSolid_->Faces()->RetrieveTo(entitiesFaces);

	for (const auto& x : entitiesFaces)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(std::dynamic_pointer_cast<Solid_Face>(x));
		auto face = std::dynamic_pointer_cast<Solid_Face>(x);

		theFaces_.push_back(std::make_shared<TonbPartData>(face));
	}

	/*QList<std::shared_ptr<Solid_Entity>> edges;
	for (int i = 0; i < theEdges_.size(); i++)
		edges.push_back(theEdges_.at(i)->theData_);

	QList<std::shared_ptr<Solid_Entity>> faces;
	for (int i = 0; i < theFaces_.size(); i++)
		faces.push_back(theFaces_.at(i)->theData_);

	((TonbPartTWI*)theParent_)->CreateFeatures(faces, model);
	((TonbPartTWI*)theParent_)->CreateFeatures(edges, model);*/
}

AutLib::TonbPartTWI::TonbPartTWI
(
	SimulationWindow* parentwindow,
	TonbTWI* parent,
	const QString & title
)
	: TonbTWI(parentwindow, parent, title)
{
	setIcon(0, QIcon(":/Images/Icons/Part/Part_Icon.png"));
	//setFlags(flags() | Qt::ItemIsEditable);

	theContextMenu_ = std::make_shared<PartContextMenu>();

	theContextMenu_->theRenameAction_ = new QAction("Rename", (QWidget*)this->GetParentWindow());
	theContextMenu_->theNewGeometryScene_ = new QAction("New Geometry Scene", (QWidget*)this->GetParentWindow());
	theContextMenu_->theExport_ = new QAction("Export", (QWidget*)this->GetParentWindow());
	theContextMenu_->theExport_->setIcon(QIcon(":/Menus/Icons/Menus/File/Export.png"));

	GetContextMenu()->addAction(theContextMenu_->theRenameAction_);
	GetContextMenu()->addAction(theContextMenu_->theNewGeometryScene_);
	GetContextMenu()->addAction(theContextMenu_->theExport_);

	QObject::connect(theContextMenu_->theRenameAction_, SIGNAL(triggered()), this, SLOT(RenameItemSlot()));
	QObject::connect(theContextMenu_->theNewGeometryScene_, SIGNAL(triggered()), this, SLOT(AddGeometrySceneSlot()));
	QObject::connect(theContextMenu_->theExport_, SIGNAL(triggered()), this, SLOT(ExportPartSlot()));

	this->FindProperty("Name")->property()->setEnabled(true);
}



AutLib::TonbPartTWI::TonbPartTWI(const TonbPartTWI & part)
	: TonbTWI(part.GetParentWindow(), part.GetParentItem(), part.text(0))
{
	setIcon(0, QIcon(":/Images/Icons/Part/Part_Icon.png"));
}

void AutLib::TonbPartTWI::CreateFeatures
(
	QList<std::shared_ptr<Solid_Entity>> features,
	std::shared_ptr<Model_Entity> model
)
{
	if (std::dynamic_pointer_cast<Solid_Face>(features.at(0)))
		theFeatures_.push_back(std::make_shared<TonbPartFeaturesTWI>(GetParentWindow(), (TonbTWI*)this, "Surfaces", features, model));
	else if (std::dynamic_pointer_cast<Solid_Paired>(features.at(0)))
		theFeatures_.push_back(std::make_shared<TonbPartFeaturesTWI>(GetParentWindow(), (TonbTWI*)this, "Curves", features, model));
}

//void AutLib::TonbPartTWI::RenameItemSlot()
//{
//	GetParentView()->editItem(this);
//}

void AutLib::TonbPartTWI::AddGeometrySceneSlot()
{
	this->GetParentView()->GetScenesItem()->AddScene(std::dynamic_pointer_cast<TonbPartTWI>(this->shared_from_this()));

	this->setSelected(false);

	emit this->GetParentView()->expandItem(this->GetParentView()->GetScenesItem()->GetScenes().at(GetParentView()->GetScenesItem()->GetScenes().size() - 1)->GetParentItem());
	this->GetParentView()->GetScenesItem()->GetScenes().last()->setSelected(true);
	emit this->GetParentView()->itemClicked(this->GetParentView()->GetScenesItem()->GetScenes().at(GetParentView()->GetScenesItem()->GetScenes().size() - 1).get(), 0);

	thePartGeometry_->thePointerToScene_ = GetParentView()->GetScenesItem()->GetScenes().at(GetParentView()->GetScenesItem()->GetScenes().size() - 1);

}

void AutLib::TonbPartTWI::ExportPartSlot()
{
	QList<QString> QfileTypes;
	QfileTypes.push_back("IGES (*.igs)");
	QfileTypes.push_back("STEP (*.stp; *.step)");
	QfileTypes.push_back("Tecplot (*.plt)");

	QString fileTypes;
	for (int i = 0; i < QfileTypes.size() - 1; i++)
	{
		fileTypes += QfileTypes.at(i);
		fileTypes += ";;";
	}
	fileTypes += QfileTypes.at(QfileTypes.size() - 1);

	QString* ext = new QString("IGES");
	QString fileName = QFileDialog::getSaveFileName((QWidget*)this->GetParentWindow(),
		tr("Export Part"), "",
		fileTypes, ext);

	if (fileName.isEmpty())
		return;
	else
	{
		thePartGeometry_->thePartEntity_->SetFileName(fileName.toStdString());
		if (*ext == "IGES (*.igs)")
		{
			thePartGeometry_->thePartEntity_->SetFileFromat(Io::EntityIO_Format_IGES);
			thePartGeometry_->thePartEntity_->ExportToFile();
		}
		else if (*ext == "STEP (*.stp; *.step)")
		{
			thePartGeometry_->thePartEntity_->SetFileFromat(Io::EntityIO_Format_STEP);
			thePartGeometry_->thePartEntity_->ExportToFile();
		}
		else if (*ext == "Tecplot (*.plt)")
		{
			thePartGeometry_->thePartEntity_->SetFileFromat(Io::EntityIO_Format_TecPlot);
			thePartGeometry_->thePartEntity_->ExportToFile();
		}
	}
}