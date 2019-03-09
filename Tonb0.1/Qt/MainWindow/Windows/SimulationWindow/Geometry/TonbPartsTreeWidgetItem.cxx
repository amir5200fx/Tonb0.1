#include <TonbPartsTreeWidgetItem.hxx>
#include <TonbPartTreeWidgetItem.hxx>
#include <TonbDisplacementTreeWidgetItem.hxx>
#include <TonbSimulationTreeWidget.hxx>
#include <TonbScenesTreeWidgetItem.hxx>
#include <QtWidgets/qaction.h>
#include <QtWidgets/qmenu.h>


AutLib::TonbPartsTreeWidgetItem::TonbPartsTreeWidgetItem(SimulationWindow * parentwindow, TonbTreeWidgetItem * parent, const QString & title)
	: TonbTreeWidgetItem(parentwindow, parent, title)
{
	
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
		theParts_.at(theParts_.size() - 1)->GetDisplacementGeometry() = item;
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
		theParts_.at(theParts_.size() - 1)->GetDisplacementGeometry() = item;
		GetParentView()->GetScenesItem()->setHidden(false);
	}
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