#include <TonbTWI.hxx>
#include <TonbSimulationTreeWidget.hxx>
#include <QtWidgets/qmenu.h>
#include <qttreepropertybrowser.h>
#include <qtvariantproperty.h>
#include <SimulationWindow.hxx>
#include <iostream>

AutLib::TonbTWI::TonbTWI
(
	SimulationWindow* parentwindow,
	TonbSimulationTreeWidget* parent,
	const QString& title
)
	: QTreeWidgetItem((QTreeWidget*)parent)
	, theParentView_(parent)
{
	setText(0, title);
	setIcon(0, QIcon(":/Menus/Icons/Menus/File/Load.png"));
	parent->addTopLevelItem(this);
	theContextMenu_ = new QMenu;

	theParentWindow_ = parentwindow;

	CreateProperty();
}

AutLib::TonbTWI::TonbTWI
(
	SimulationWindow* parentwindow,
	TonbTWI* parent,
	const QString& title
)
	: QTreeWidgetItem(parent)
	, theParentItem_(parent)
{
	setText(0, title);
	setIcon(0, QIcon(":/Menus/Icons/Menus/File/Load.png"));
	addChild(parent);
	theContextMenu_ = new QMenu;

	theParentWindow_ = parentwindow;

	theParentView_ = parent->GetParentView();

	CreateProperty();
}

void AutLib::TonbTWI::CreateProperty()
{
	theProperty_ = std::make_shared<QtTreePropertyBrowser>();

	theVariantPropertyManager_ = std::make_shared<QtVariantPropertyManager>();
	theVariantEditorFactory_ = std::make_shared<QtVariantEditorFactory>();

	theProperty_->setFactoryForManager(theVariantPropertyManager_.get(), theVariantEditorFactory_.get());

	QtProperty *topItem = theVariantPropertyManager_->addProperty(QtVariantPropertyManager::groupTypeId(), QLatin1String("Properties"));

	QtVariantProperty* item = theVariantPropertyManager_->addProperty(QVariant::String, QLatin1String("Name"));
	item->setValue(this->text(0));
	item->setPropertyId(item->propertyName());
	item->setEnabled(false);
	topItem->addSubProperty(item);

	theProperty_->addProperty(topItem);
	theProperty_->setPropertiesWithoutValueMarked(true);
	theProperty_->setRootIsDecorated(false);
	
	connect(theVariantPropertyManager_.get(),
		SIGNAL(valueChanged(QtProperty *, const QVariant &)),
		this,
		SLOT(PropertyChangedSlot(QtProperty *, const QVariant &)));
}

QtBrowserItem * AutLib::TonbTWI::FindProperty(QtBrowserItem * property, const QString & IdName)
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

QtBrowserItem * AutLib::TonbTWI::FindProperty(const QString & IdName)
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

QString AutLib::TonbTWI::CorrectName(TonbTWI* parentItem, const QString & name)
{
	parentItem->sortChildren(0, Qt::AscendingOrder);

	QString output;

	int nameNumber = 1;
	for (int i = 0; i < parentItem->childCount(); i++)
	{
		if (nameNumber < 10)
		{
			if (parentItem->child(i)->text(0) == (name + " 0" + QString::number(nameNumber)))
				nameNumber++;
		}
		else
				if (parentItem->child(i)->text(0) == (name + " " + QString::number(nameNumber)))
					nameNumber++;
	}
	if(nameNumber < 10)
		output = name + " 0" + QString::number(nameNumber);
	else
		output = name + " " + QString::number(nameNumber);
	return output;
}

void AutLib::TonbTWI::RenameItemSlot()
{
	theProperty_->editItem(FindProperty("Name"));
}

void AutLib::TonbTWI::PropertyChangedSlot(QtProperty * property, const QVariant & val)
{
	if (property->propertyName().toStdString() == "Name")
		this->setText(0, val.toString());
	if (property->propertyName().toStdString() == "Face Color")
		UpdateGeometryColorSlot(property, val);
}