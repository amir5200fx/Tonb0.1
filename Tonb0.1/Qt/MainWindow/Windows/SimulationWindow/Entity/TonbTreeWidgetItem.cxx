#include <TonbTreeWidgetItem.hxx>
#include <TonbSimulationTreeWidget.hxx>
#include <QtWidgets/qmenu.h>
#include <qttreepropertybrowser.h>
#include <qtvariantproperty.h>
#include <iostream>

AutLib::TonbTreeWidgetItem::TonbTreeWidgetItem(SimulationWindow* parentwindow, TonbSimulationTreeWidget * parent, const QString& title)
	: QTreeWidgetItem((QTreeWidget*)parent)
	, theParentView_(parent)
{
	setText(0, title);
	setIcon(0, QIcon(":/Menus/Icons/Menus/File/Load.png"));
	parent->addTopLevelItem(this);
	theMenu_ = new QMenu;

	theParentWindow_ = parentwindow;

	CreateProperty();
}

AutLib::TonbTreeWidgetItem::TonbTreeWidgetItem(SimulationWindow* parentwindow, TonbTreeWidgetItem* parent, const QString& title)
	: QTreeWidgetItem(parent)
	, theParentItem_(parent)
{
	setText(0, title);
	setIcon(0, QIcon(":/Menus/Icons/Menus/File/Load.png"));
	addChild(parent);
	theMenu_ = new QMenu;

	theParentWindow_ = parentwindow;

	theParentView_ = parent->GetParentView();

	CreateProperty();
}

void AutLib::TonbTreeWidgetItem::CreateProperty()
{
	theProperty_ = new QtTreePropertyBrowser(0);

	theVariantManager_ = new QtVariantPropertyManager();
	theVriantFactory_ = new QtVariantEditorFactory();

	theProperty_->setFactoryForManager(theVariantManager_, theVriantFactory_);

	QtProperty *topItem = theVariantManager_->addProperty(QtVariantPropertyManager::groupTypeId(), QLatin1String("Properties"));

	QtVariantProperty* item = theVariantManager_->addProperty(QVariant::String, QLatin1String("Name"));
	item->setValue(this->text(0));
	item->setPropertyId(item->propertyName());
	item->setEnabled(false);
	topItem->addSubProperty(item);

	theProperty_->addProperty(topItem);
	theProperty_->setPropertiesWithoutValueMarked(true);
	theProperty_->setRootIsDecorated(false);
	
	connect(theVariantManager_,
		SIGNAL(valueChanged(QtProperty *, const QVariant &)),
		this,
		SLOT(PropertyChangedSlot(QtProperty *, const QVariant &)));
}

QtBrowserItem * AutLib::TonbTreeWidgetItem::FindProperty(QtBrowserItem * property, const QString & IdName)
{
	QtBrowserItem* result = NULL;
	for (int i = 0; i < property->children().size(); i++)
	{
		if (property->children().at(i)->property()->propertyId() == IdName)
			return property->children().at(i);
		result = FindProperty(property->children().at(i), IdName);
	}
	return result;
}

QtBrowserItem * AutLib::TonbTreeWidgetItem::FindProperty(const QString & IdName)
{
	QtBrowserItem* result = NULL;
	QList <QtBrowserItem*> topLevelItems = theProperty_->topLevelItems();
	for (int i = 0; i < topLevelItems.size(); i++)
	{
		if (topLevelItems.at(i)->property()->propertyId() == IdName)
			return theProperty_->topLevelItems().at(i);
		result = FindProperty(topLevelItems.at(i), IdName);
		if (result)
			return result;
	}
	return NULL;
}

QString AutLib::TonbTreeWidgetItem::CorrectName(TonbTreeWidgetItem * parentItem, const QString & name)
{
	parentItem->sortChildren(0, Qt::AscendingOrder);

	QString output;

	int nameNumber = 1;
	for (int i = 0; i < parentItem->childCount(); i++)
	{
		if (parentItem->child(i)->text(0) == (name + " " + QString::number(nameNumber)))
		{
			nameNumber++;
		}
	}
	output = name + " " + QString::number(nameNumber);
	return output;
}

void AutLib::TonbTreeWidgetItem::RenameItemSlot()
{
	theProperty_->editItem(FindProperty("Name"));
}

void AutLib::TonbTreeWidgetItem::PropertyChangedSlot(QtProperty * property, const QVariant & val)
{
	if (property->propertyName().toStdString() == "Name")
		this->setText(0, val.toString());
	if (property->propertyName().toStdString() == "Face Color")
		UpdateGeometryColorSlot(property, val);
}