#include <TonbPartsTWI.hxx>
#include <TonbPartTWI.hxx>
#include <TonbDisplacementTWI.hxx>
#include <TonbSimulationTreeWidget.hxx>
#include <TonbScenesTWI.hxx>
#include <QtWidgets/qaction.h>
#include <QtWidgets/qmenu.h>

//#include <Model_Entity.hxx>
#include <Vessels_Displacements.hxx>

#include <Cad3d_Solid.hxx>

#include <Model_Box.hxx>
#include <Model_Cone.hxx>
#include <Model_Cylinder.hxx>
#include <Model_Sphere.hxx>
#include <Model_Torus.hxx>


AutLib::TonbPartsTWI::TonbPartsTWI
(
	SimulationWindow* parentwindow,
	TonbTWI* parent,
	const QString & title
)
	: TonbTWI(parentwindow, parent, title)
{
	CreateMenu();
}

std::shared_ptr<AutLib::TonbPartTWI> AutLib::TonbPartsTWI::GetPart(const QString & partName) const
{
	for (int i = 0; i < theParts_.size(); i++)
	{
		if (partName == theParts_.at(i)->text(0))
			return theParts_.at(i);
		else
			return NULL;
	}
}

int AutLib::TonbPartsTWI::GetPartIndex(const QString & partName) const
{
	for (int i = 0; i < theParts_.size(); i++)
	{
		if (partName == theParts_.at(i)->text(0))
			return i;
	}
	return -1;
}

void AutLib::TonbPartsTWI::AddPart(std::shared_ptr<TonbPartTWI> part)
{
	theParts_.push_back(part);
}

void AutLib::TonbPartsTWI::AddPart(std::shared_ptr<TonbDisplacementTWI> item, const QString & text)
{
	if (GetPartIndex(text) != -1)
	{
		AddPart(item, text + " (Copy)");
	}
	else
	{
		theParts_.push_back(std::make_shared<TonbPartTWI>(item->GetParentWindow(), (TonbTWI*)this, text));
		theParts_.at(theParts_.size() - 1)->GetPartGeometry() = std::make_shared<TonbPartTWI::TonbPart>(item->GetHull(), item);
		theParts_.at(theParts_.size() - 1)->GetPartGeometry()->thePartEntity_ = item->GetHull();
	}
}

void AutLib::TonbPartsTWI::AddPart(std::shared_ptr<TonbDisplacementTWI> item)
{
	/*if (GetPartIndex(item->text(0)) != -1)
	{
		AddPart(item, item->text(0) + " (Copy)");
	}*/
	/*else
	{*/
	theParts_.push_back(std::make_shared<TonbPartTWI>(item->GetParentWindow(), (TonbTWI*)this, item->text(0)));
	theParts_.at(theParts_.size() - 1)->GetPartGeometry() = std::make_shared<TonbPartTWI::TonbPart>(item->GetHull(), item);
	theParts_.at(theParts_.size() - 1)->GetPartGeometry()->thePartEntity_ = item->GetHull();

	QList<std::shared_ptr<Solid_Entity>> edges;
	for (int i = 0; i < theParts_.at(theParts_.size() - 1)->GetPartGeometry()->theEdges_.size(); i++)
		edges.push_back(theParts_.at(theParts_.size() - 1)->GetPartGeometry()->theEdges_.at(i)->theData_);

	QList<std::shared_ptr<Solid_Entity>> faces;
	for (int i = 0; i < theParts_.at(theParts_.size() - 1)->GetPartGeometry()->theFaces_.size(); i++)
		faces.push_back(theParts_.at(theParts_.size() - 1)->GetPartGeometry()->theFaces_.at(i)->theData_);

	theParts_.at(theParts_.size() - 1)->CreateFeatures(faces, item->GetHull());
	theParts_.at(theParts_.size() - 1)->CreateFeatures(edges, item->GetHull());

	this->sortChildren(0, Qt::AscendingOrder);
	//GetParentView()->GetScenesItem()->setHidden(false);
	//}
}

void AutLib::TonbPartsTWI::AddPart(std::shared_ptr<Model_Entity> part, const QString & name)
{
	theParts_.push_back(std::make_shared<TonbPartTWI>(this->GetParentWindow(), this, TonbTWI::CorrectName(this, name)));
	part->SetName(theParts_.at(theParts_.size() - 1)->text(0).toStdString());
	theParts_.at(theParts_.size() - 1)->GetPartGeometry() = 
		std::make_shared<TonbPartTWI::TonbPart>(part, theParts_.at(theParts_.size() - 1));

	QList<std::shared_ptr<Solid_Entity>> edges;
	for (int i = 0; i < theParts_.at(theParts_.size() - 1)->GetPartGeometry()->theEdges_.size(); i++)
		edges.push_back(theParts_.at(theParts_.size() - 1)->GetPartGeometry()->theEdges_.at(i)->theData_);

	QList<std::shared_ptr<Solid_Entity>> faces;
	for (int i = 0; i < theParts_.at(theParts_.size() - 1)->GetPartGeometry()->theFaces_.size(); i++)
		faces.push_back(theParts_.at(theParts_.size() - 1)->GetPartGeometry()->theFaces_.at(i)->theData_);

	theParts_.at(theParts_.size() - 1)->CreateFeatures(faces, part);
	theParts_.at(theParts_.size() - 1)->CreateFeatures(edges, part);

	this->sortChildren(0, Qt::AscendingOrder);
}

void AutLib::TonbPartsTWI::RemovePart(const QString & partName)
{
	theParts_.removeAt(GetPartIndex(partName));
}

void AutLib::TonbPartsTWI::RemovePart(std::shared_ptr<TonbPartTWI> part)
{
	theParts_.removeAt(GetPartIndex(part->text(0)));
}

void AutLib::TonbPartsTWI::RemovePartAt(int Index)
{
	theParts_.removeAt(Index);
}

void AutLib::TonbPartsTWI::CreateMenu()
{
	thePartsItemContextMenu_ = std::make_shared<PartsItemContextMenu>();

	thePartsItemContextMenu_->theNewShapePart_ = new QMenu("New Shape Part", (QWidget*)this->GetParentWindow());
	this->GetContextMenu()->addMenu(thePartsItemContextMenu_->theNewShapePart_);

	thePartsItemContextMenu_->theNewShapePartBlock_ = new QAction("Block", (QWidget*)this->GetParentWindow());
	thePartsItemContextMenu_->theNewShapePartCone_ = new QAction("Cone", (QWidget*)this->GetParentWindow());
	thePartsItemContextMenu_->theNewShapePartCylinder_ = new QAction("Cylinder", (QWidget*)this->GetParentWindow());
	thePartsItemContextMenu_->theNewShapePartSphere_ = new QAction("Sphere", (QWidget*)this->GetParentWindow());
	thePartsItemContextMenu_->theNewShapePartTorus_ = new QAction("Torus", (QWidget*)this->GetParentWindow());

	thePartsItemContextMenu_->theNewShapePart_->addAction(thePartsItemContextMenu_->theNewShapePartBlock_);
	thePartsItemContextMenu_->theNewShapePart_->addAction(thePartsItemContextMenu_->theNewShapePartCone_);
	thePartsItemContextMenu_->theNewShapePart_->addAction(thePartsItemContextMenu_->theNewShapePartCylinder_);
	thePartsItemContextMenu_->theNewShapePart_->addAction(thePartsItemContextMenu_->theNewShapePartSphere_);
	thePartsItemContextMenu_->theNewShapePart_->addAction(thePartsItemContextMenu_->theNewShapePartTorus_);

	connect(thePartsItemContextMenu_->theNewShapePartBlock_, SIGNAL(triggered()), this, SLOT(AddBlock()));
	connect(thePartsItemContextMenu_->theNewShapePartCone_, SIGNAL(triggered()), this, SLOT(AddCone()));
	connect(thePartsItemContextMenu_->theNewShapePartCylinder_, SIGNAL(triggered()), this, SLOT(AddCylinder()));
	connect(thePartsItemContextMenu_->theNewShapePartSphere_, SIGNAL(triggered()), this, SLOT(AddShpere()));
	connect(thePartsItemContextMenu_->theNewShapePartTorus_, SIGNAL(triggered()), this, SLOT(AddTorus()));
}

void AutLib::TonbPartsTWI::AddBlock()
{
	std::shared_ptr<Model_Box> theBox = std::make_shared<Model_Box>(1.0, 1.0, 1.0);
	theBox->Make();
	AddPart(theBox, "Block");
}

void AutLib::TonbPartsTWI::AddCone()
{
	std::shared_ptr<Model_Cone> theCone = std::make_shared<Model_Cone>(1.0, 0.5, 2.0);
	theCone->Make();
	AddPart(theCone, "Cone");
}

void AutLib::TonbPartsTWI::AddCylinder()
{
	std::shared_ptr<Model_Cylinder> theCylinder = std::make_shared<Model_Cylinder>(1.0, 2.0);
	theCylinder->Make();
	AddPart(theCylinder, "Cylinder");
}

void AutLib::TonbPartsTWI::AddShpere()
{
	std::shared_ptr<Model_Sphere> theSphere = std::make_shared<Model_Sphere>(1.0);
	theSphere->Make();
	AddPart(theSphere, "Sphere");
}

void AutLib::TonbPartsTWI::AddTorus()
{
	std::shared_ptr<Model_Torus> theTorus = std::make_shared<Model_Torus>(2.0, 1.0);
	theTorus->Make();
	AddPart(theTorus, "Torus");
}