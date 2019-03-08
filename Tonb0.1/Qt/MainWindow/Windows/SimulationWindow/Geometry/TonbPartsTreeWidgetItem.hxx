#pragma once
#ifndef _TonbPartsTreeWidgetItem_Header
#define _TonbPartsTreeWidgetItem_Header

#include <TonbTreeWidgetItem.hxx>

namespace AutLib
{

	class TonbPartTreeWidgetItem;
	class TonbDisplacementTreeWidgetItem;
	class SimulationWindow;

	class TonbPartsTreeWidgetItem
		: public TonbTreeWidgetItem
	{

	private:

		QList<TonbPartTreeWidgetItem*> theParts_;

	public:

		TonbPartsTreeWidgetItem(SimulationWindow* parentwindow = nullptr, TonbTreeWidgetItem* parent = nullptr, const QString& title = "Parts");

		int GetNumberOfParts() const
		{
			return theParts_.size();
		}

		TonbPartTreeWidgetItem* GetPart(const QString& partName) const;

		int GetPartIndex(const QString& partName) const;

		void AddPart(TonbPartTreeWidgetItem* part);

		void AddPart(TonbDisplacementTreeWidgetItem* item, const QString& text);

		void AddPart(TonbDisplacementTreeWidgetItem* item);

		void RemovePart(const QString& partName);

		void RemovePart(TonbPartTreeWidgetItem* part);

		void RemovePartAt(int Index);

	};
}

#endif // !_TonbPartsTreeWidgetItem_Header
