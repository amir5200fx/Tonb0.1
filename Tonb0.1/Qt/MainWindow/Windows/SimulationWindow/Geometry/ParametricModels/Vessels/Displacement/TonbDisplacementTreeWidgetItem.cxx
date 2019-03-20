#include <TonbDisplacementTreeWidgetItem.hxx>
#include <TonbSimulationTreeWidget.hxx>
#include <TonbGeometryTreeWidgetItem.hxx>
#include <TonbPartsTreeWidgetItem.hxx>
#include <TonbPartTreeWidgetItem.hxx>
#include <QtWidgets/qaction.h>
#include <QtWidgets/qmenu.h>
#include <Vessels_DispNo1.hxx>
#include <TopoDS_Shape.hxx>
#include <qtvariantproperty.h>
#include <qttreepropertybrowser.h>
#include <QtCore/QSet>

AutLib::TonbDisplacementTreeWidgetItem::TonbDisplacementTreeWidgetItem(SimulationWindow* parentwindow, TonbTreeWidgetItem * parent, const QString & title)
	: TonbTreeWidgetItem(parentwindow, parent, title)
{
	//setFlags(flags() | Qt::ItemIsEditable);

	CreateMenu();

	emit this->GetParentView()->itemClicked(this, 0);

	//CreateHull();
}

//void AutLib::TonbDisplacementTreeWidgetItem::RenameItemSlot()
//{
//	//GetParentView()->editItem(this);
//	//this->GetProperty()->editItem(this->GetProperty()->topLevelItems()[0]->children().at(0));
//	//std::cout << this->FindProperty("Name")->property()->propertyName().toStdString() << std::endl;
//	this->GetProperty()->editItem(this->FindProperty("Name"));
//}

void AutLib::TonbDisplacementTreeWidgetItem::CreateHull(bool Symmetry)
{
	if (Symmetry)
		theHull_ = std::make_shared<DispNo1_HullPatch>();
		//theHull_ = new DispNo1_HullPatch;
	else
		theHull_ = std::make_shared<DispNo1_BareHull>();
		//theHull_ = new DispNo1_BareHull;

	//theHull_->Perform();

	this->CreateProperties();

	/*if (!Symmetry)
	{
		std::cout << std::dynamic_pointer_cast<DispNo1_BareHull>(theHull_)->typeName << std::endl;
	}
	else
		std::cout << theHull_->typeName << std::endl;*/

}

void AutLib::TonbDisplacementTreeWidgetItem::DiscreteHull()
{
	theHull_->Discrete();
}

const TopoDS_Shape & AutLib::TonbDisplacementTreeWidgetItem::GetHullEntity() const
{
	return theHull_->GetEntity();
}

//AutLib::TopoDS_Shape& AutLib::TonbDisplacementTreeWidgetItem::GetHullEntity()
//{
//	return theHull_->Entity();
//}

void AutLib::TonbDisplacementTreeWidgetItem::CreateMenu()
{
	theContextMenu_ = new DisplacementContextMenu;

	theContextMenu_->theRenameAction_ = new QAction("Rename", (QWidget*)this->GetParentWindow());
	GetContextMenu()->addAction(theContextMenu_->theRenameAction_);

	theContextMenu_->theNewGeometryPartAction_ = new QAction("New Geometry Part", (QWidget*)this->GetParentWindow());
	GetContextMenu()->addAction(theContextMenu_->theNewGeometryPartAction_);

	QObject::connect(theContextMenu_->theRenameAction_, SIGNAL(triggered()), this, SLOT(RenameItemSlot()));

	QObject::connect(theContextMenu_->theNewGeometryPartAction_, SIGNAL(triggered()), this, SLOT(NewGeometryPartSlot()));
}

#define AddPropertyToPropertiesWindow(variantPropertyManager, hull, param, topItem, item, name)\
item = variantPropertyManager->addProperty(QVariant::Double, QLatin1String(name));\
item->setValue(hull->param().Value());\
item->setPropertyId(hull->param().Name().c_str());\
topItem->addSubProperty(item);

void AutLib::TonbDisplacementTreeWidgetItem::CreateProperties()
{
	QtProperty* topItem = this->GetVariantPropertyManager()->addProperty(QtVariantPropertyManager::groupTypeId(), QLatin1String("Main Dimension"));
	topItem->setPropertyId(topItem->propertyName());

	QtVariantProperty* item;
	AddPropertyToPropertiesWindow(this->GetVariantPropertyManager(), theHull_, LengthOnDeck, topItem, item, "Length On Deck");
	AddPropertyToPropertiesWindow(this->GetVariantPropertyManager(), theHull_, BeamOnDeck, topItem, item, "Beam On Deck");
	AddPropertyToPropertiesWindow(this->GetVariantPropertyManager(), theHull_, DepthAtBow, topItem, item, "Depth At Bow");
	AddPropertyToPropertiesWindow(this->GetVariantPropertyManager(), theHull_, DepthAtTransom, topItem, item, "Depth At Transom");
	AddPropertyToPropertiesWindow(this->GetVariantPropertyManager(), theHull_, Draft, topItem, item, "Draft");
	AddPropertyToPropertiesWindow(this->GetVariantPropertyManager(), theHull_, TransomHeight, topItem, item, "Transom Height");
	this->GetProperty()->addProperty(topItem);

	topItem = this->GetVariantPropertyManager()->addProperty(QtVariantPropertyManager::groupTypeId(), QLatin1String("Stem Dimension"));
	topItem->setPropertyId(topItem->propertyName());
	AddPropertyToPropertiesWindow(this->GetVariantPropertyManager(), theHull_, BowRounding, topItem, item, "Bow Rounding");
	AddPropertyToPropertiesWindow(this->GetVariantPropertyManager(), theHull_, ForeFootShape, topItem, item, "Fore Foot Shape");
	AddPropertyToPropertiesWindow(this->GetVariantPropertyManager(), theHull_, StemRake, topItem, item, "Stem Rake");
	this->GetProperty()->addProperty(topItem);

	topItem = this->GetVariantPropertyManager()->addProperty(QtVariantPropertyManager::groupTypeId(), QLatin1String("Forward Section"));
	topItem->setPropertyId(topItem->propertyName());
	AddPropertyToPropertiesWindow(this->GetVariantPropertyManager(), theHull_, FwdSection().Tightness, topItem, item, "Tightness");
	AddPropertyToPropertiesWindow(this->GetVariantPropertyManager(), theHull_, FwdSection().DeadRise, topItem, item, "Dead Rise");
	AddPropertyToPropertiesWindow(this->GetVariantPropertyManager(), theHull_, FwdSection().SideSlope, topItem, item, "Side Slope");
	AddPropertyToPropertiesWindow(this->GetVariantPropertyManager(), theHull_, FwdSection().Flare, topItem, item, "Flare");
	this->GetProperty()->addProperty(topItem);

	topItem = this->GetVariantPropertyManager()->addProperty(QtVariantPropertyManager::groupTypeId(), QLatin1String("Midlle Section"));
	topItem->setPropertyId(topItem->propertyName());
	AddPropertyToPropertiesWindow(this->GetVariantPropertyManager(), theHull_, MidSection().Tightness, topItem, item, "Tightness");
	AddPropertyToPropertiesWindow(this->GetVariantPropertyManager(), theHull_, MidSection().DeadRise, topItem, item, "Dead Rise");
	AddPropertyToPropertiesWindow(this->GetVariantPropertyManager(), theHull_, MidSection().SideSlope, topItem, item, "Side Slope");
	AddPropertyToPropertiesWindow(this->GetVariantPropertyManager(), theHull_, MidSection().Flare, topItem, item, "Flare");
	this->GetProperty()->addProperty(topItem);

	topItem = this->GetVariantPropertyManager()->addProperty(QtVariantPropertyManager::groupTypeId(), QLatin1String("Aft Section"));
	topItem->setPropertyId(topItem->propertyName());
	AddPropertyToPropertiesWindow(this->GetVariantPropertyManager(), theHull_, AftSection().Tightness, topItem, item, "Tightness");
	AddPropertyToPropertiesWindow(this->GetVariantPropertyManager(), theHull_, AftSection().DeadRise, topItem, item, "Dead Rise");
	AddPropertyToPropertiesWindow(this->GetVariantPropertyManager(), theHull_, AftSection().SideSlope, topItem, item, "Side Slope");
	AddPropertyToPropertiesWindow(this->GetVariantPropertyManager(), theHull_, AftSection().Flare, topItem, item, "Flare");
	this->GetProperty()->addProperty(topItem);

	topItem = this->GetVariantPropertyManager()->addProperty(QtVariantPropertyManager::groupTypeId(), QLatin1String("Transom"));
	topItem->setPropertyId(topItem->propertyName());
	AddPropertyToPropertiesWindow(this->GetVariantPropertyManager(), theHull_, Rake, topItem, item, "Rake");
	AddPropertyToPropertiesWindow(this->GetVariantPropertyManager(), theHull_, Width, topItem, item, "Width");
	this->GetProperty()->addProperty(topItem);

	topItem = this->GetVariantPropertyManager()->addProperty(QtVariantPropertyManager::groupTypeId(), QLatin1String("Keel"));
	topItem->setPropertyId(topItem->propertyName());
	AddPropertyToPropertiesWindow(this->GetVariantPropertyManager(), theHull_, RisePoint, topItem, item, "Rise Point");
	AddPropertyToPropertiesWindow(this->GetVariantPropertyManager(), theHull_, Position, topItem, item, "Position");
	AddPropertyToPropertiesWindow(this->GetVariantPropertyManager(), theHull_, RiseSlope, topItem, item, "Rise Slope");
	AddPropertyToPropertiesWindow(this->GetVariantPropertyManager(), theHull_, TransomSlope, topItem, item, "Transom Slope");
	this->GetProperty()->addProperty(topItem);

	topItem = this->GetVariantPropertyManager()->addProperty(QtVariantPropertyManager::groupTypeId(), QLatin1String("Hull"));
	topItem->setPropertyId(topItem->propertyName());
	AddPropertyToPropertiesWindow(this->GetVariantPropertyManager(), theHull_, MaxAreaLocation, topItem, item, "Max Area Location");
	AddPropertyToPropertiesWindow(this->GetVariantPropertyManager(), theHull_, FwdFullness, topItem, item, "Fwd Fullness");
	AddPropertyToPropertiesWindow(this->GetVariantPropertyManager(), theHull_, AftFullness, topItem, item, "Aft Fullness");
	this->GetProperty()->addProperty(topItem);

	/*connect(this->GetVariantPropertyManager(),
		SIGNAL(valueChanged(QtProperty *, const QVariant &)),
		this,
		SLOT(PropertyChangedSlot(QtProperty *, const QVariant &)));*/
}

void AutLib::TonbDisplacementTreeWidgetItem::NewGeometryPartSlot()
{
	theHull_->Perform();
	GetParentView()->GetGeometryItem()->GetPartsItem()->AddPart(this);

	this->setSelected(false);

	emit this->GetParentView()->expandItem(this->GetParentView()->GetGeometryItem()->GetPartsItem()->GetParts().last()->GetParentItem());
	this->GetParentView()->GetGeometryItem()->GetPartsItem()->GetParts().last()->setSelected(true);
	emit this->GetParentView()->itemClicked(this->GetParentView()->GetGeometryItem()->GetPartsItem()->GetParts().last(), 0);
}

#define SetParameterToHull(hull, parameter, prop, val)\
if (hull->parameter().Name().c_str() == prop->propertyId().toStdString())\
{\
	hull->parameter().Value() = val.toDouble();\
}\
	//hull->Perform();

void AutLib::TonbDisplacementTreeWidgetItem::PropertyChangedSlot(QtProperty * property, const QVariant & val)
{
	SetParameterToHull(theHull_, Draft, property, val);
	SetParameterToHull(theHull_, TransomHeight, property, val);
	SetParameterToHull(theHull_, DepthAtBow, property, val);
	SetParameterToHull(theHull_, DepthAtTransom, property, val);
	SetParameterToHull(theHull_, BeamOnDeck, property, val);
	SetParameterToHull(theHull_, LengthOnDeck, property, val);

	SetParameterToHull(theHull_, AftSection().Tightness, property, val);
	SetParameterToHull(theHull_, AftSection().DeadRise, property, val);
	SetParameterToHull(theHull_, AftSection().SideSlope, property, val);
	SetParameterToHull(theHull_, AftSection().Flare, property, val);

	SetParameterToHull(theHull_, MidSection().Tightness, property, val);
	SetParameterToHull(theHull_, MidSection().DeadRise, property, val);
	SetParameterToHull(theHull_, MidSection().SideSlope, property, val);
	SetParameterToHull(theHull_, MidSection().Flare, property, val);

	SetParameterToHull(theHull_, FwdSection().Tightness, property, val);
	SetParameterToHull(theHull_, FwdSection().DeadRise, property, val);
	SetParameterToHull(theHull_, FwdSection().SideSlope, property, val);
	SetParameterToHull(theHull_, FwdSection().Flare, property, val);

	SetParameterToHull(theHull_, Position, property, val);
	SetParameterToHull(theHull_, RisePoint, property, val);
	SetParameterToHull(theHull_, RiseSlope, property, val);
	SetParameterToHull(theHull_, TransomSlope, property, val);

	SetParameterToHull(theHull_, BowRounding, property, val);
	SetParameterToHull(theHull_, StemRake, property, val);
	SetParameterToHull(theHull_, ForeFootShape, property, val);

	SetParameterToHull(theHull_, Rake, property, val);
	SetParameterToHull(theHull_, Width, property, val);

	SetParameterToHull(theHull_, MaxAreaLocation, property, val);
	SetParameterToHull(theHull_, FwdFullness, property, val);
	SetParameterToHull(theHull_, AftFullness, property, val);

	if (property->propertyName().toStdString() == "Name")
		this->setText(0, val.toString());
}