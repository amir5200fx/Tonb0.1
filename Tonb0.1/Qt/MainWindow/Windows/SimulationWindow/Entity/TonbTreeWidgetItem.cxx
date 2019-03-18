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

	QtVariantPropertyManager *variantManager = new QtVariantPropertyManager();
	QtVariantEditorFactory *variantFactory = new QtVariantEditorFactory();

	theProperty_->setFactoryForManager(variantManager, variantFactory);

	QtProperty *topItem = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(), QLatin1String("Properties"));

	QtVariantProperty* item = variantManager->addProperty(QVariant::String, QLatin1String("Name"));
	item->setValue(this->text(0));
	//item->setEnabled(false);
	topItem->addSubProperty(item);

	theProperty_->addProperty(topItem);
	//theProperty_->setBackgroundColor(theProperty_->items(theProperty_->properties()[0])[0], QColor(255, 255, 255));
	//std::cout << theProperty_->properties()[0]->propertyName().toStdString() << ": ";
	//std::cout << theProperty_->properties()[0]->valueText().toStdString() << std::endl;
	theProperty_->setPropertiesWithoutValueMarked(true);
	theProperty_->setRootIsDecorated(false);
}