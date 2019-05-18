#include <TonbPartsTreeWidgetItem.hxx>
#include <TonbPartTreeWidgetItem.hxx>
#include <TonbDisplacementTreeWidgetItem.hxx>
#include <TonbSimulationTreeWidget.hxx>
#include <TonbScenesTreeWidgetItem.hxx>
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


AutLib::TonbPartsTreeWidgetItem::TonbPartsTreeWidgetItem(SimulationWindow * parentwindow, TonbTreeWidgetItem * parent, const QString & title)
	: TonbTreeWidgetItem(parentwindow, parent, title)
{
	CreateMenu();
}

AutLib::TonbPartTreeWidgetItem * AutLib::TonbPartsTreeWidgetItem::GetPart(const QString & partName) const
{
	for (int i = 0; i < theParts_.size(); i++)
	{
		if (partName == theParts_.at(i)->text(0))
			return theParts_.at(i);
		else
			return NULL;
	}
}

int AutLib::TonbPartsTreeWidgetItem::GetPartIndex(const QString & partName) const
{
	for (int i = 0; i < theParts_.size(); i++)
	{
		if (partName == theParts_.at(i)->text(0))
			return i;
	}
	return -1;
}

void AutLib::TonbPartsTreeWidgetItem::AddPart(TonbPartTreeWidgetItem * part)
{
	theParts_.push_back(part);
}

void AutLib::TonbPartsTreeWidgetItem::AddPart(TonbDisplacementTreeWidgetItem * item, const QString & text)
{
	if (GetPartIndex(text) != -1)
	{
		AddPart(item, text + " (Copy)");
	}
	else
	{
		theParts_.push_back(new TonbPartTreeWidgetItem(item->GetParentWindow(), this, text));
		theParts_.at(theParts_.size() - 1)->GetPartGeometry()->thePartEntity_ = item->GetHull();
	}
}

void AutLib::TonbPartsTreeWidgetItem::AddPart(TonbDisplacementTreeWidgetItem * item)
{
	if (GetPartIndex(item->text(0)) != -1)
	{
		AddPart(item, item->text(0) + " (Copy)");
	}
	else
	{
		theParts_.push_back(new TonbPartTreeWidgetItem(item->GetParentWindow(), this, item->text(0)));
		theParts_.at(theParts_.size() - 1)->GetPartGeometry()->thePartEntity_ = item->GetHull();
		GetParentView()->GetScenesItem()->setHidden(false);
	}
}

void AutLib::TonbPartsTreeWidgetItem::AddPart(std::shared_ptr<Model_Entity> part, const QString & name)
{
	theParts_.push_back(new TonbPartTreeWidgetItem(this->GetParentWindow(), this, TonbTreeWidgetItem::CorrectName(this, name)));
	part->SetName(theParts_.at(theParts_.size() - 1)->text(0).toStdString());
	theParts_.at(theParts_.size() - 1)->GetPartGeometry() = 
		std::make_shared<TonbPartTreeWidgetItem::TonbPart>(part);

	this->sortChildren(0, Qt::AscendingOrder);
}

void AutLib::TonbPartsTreeWidgetItem::RemovePart(const QString & partName)
{
	theParts_.removeAt(GetPartIndex(partName));
}

void AutLib::TonbPartsTreeWidgetItem::RemovePart(TonbPartTreeWidgetItem * part)
{
	theParts_.removeAt(GetPartIndex(part->text(0)));
}

void AutLib::TonbPartsTreeWidgetItem::RemovePartAt(int Index)
{
	theParts_.removeAt(Index);
}

void AutLib::TonbPartsTreeWidgetItem::CreateMenu()
{
	thePartsItemContextMenu_ = new PartsItemContextMenu;

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

void AutLib::TonbPartsTreeWidgetItem::AddBlock()
{
	std::shared_ptr<Model_Box> theBox = std::make_shared<Model_Box>(1.0, 1.0, 1.0);
	theBox->Make();
	AddPart(theBox, "Block");
}

void AutLib::TonbPartsTreeWidgetItem::AddCone()
{
	std::shared_ptr<Model_Cone> theCone = std::make_shared<Model_Cone>(1.0, 0.5, 2.0);
	theCone->Make();
	AddPart(theCone, "Cone");
}

void AutLib::TonbPartsTreeWidgetItem::AddCylinder()
{
	std::shared_ptr<Model_Cylinder> theCylinder = std::make_shared<Model_Cylinder>(1.0, 2.0);
	theCylinder->Make();
	AddPart(theCylinder, "Cylinder");
}

void AutLib::TonbPartsTreeWidgetItem::AddShpere()
{
	std::shared_ptr<Model_Sphere> theSphere = std::make_shared<Model_Sphere>(1.0);
	theSphere->Make();
	AddPart(theSphere, "Sphere");
}

void AutLib::TonbPartsTreeWidgetItem::AddTorus()
{
	std::shared_ptr<Model_Torus> theTorus = std::make_shared<Model_Torus>(2.0, 1.0);
	theTorus->Make();
	AddPart(theTorus, "Torus");
}