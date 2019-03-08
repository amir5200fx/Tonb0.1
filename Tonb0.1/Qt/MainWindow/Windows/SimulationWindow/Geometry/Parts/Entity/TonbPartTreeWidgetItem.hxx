#pragma once
#ifndef _TonbPartTreeWidgetItem_Header
#define _TonbPartTreeWidgetItem_Header

#include <TonbTreeWidgetItem.hxx>

namespace AutLib
{

	class SimulationWindow;

	class TonbPartTreeWidgetItem
		: public QObject
		, public TonbTreeWidgetItem
	{

		struct PartContextMenu
		{
			QAction* theRenameAction_ = NULL;
		};

		Q_OBJECT

	private:

		PartContextMenu* theContextMenu_ = NULL;

	public:

		TonbPartTreeWidgetItem(SimulationWindow* parentwindow = nullptr, TonbTreeWidgetItem* parent = nullptr, const QString& title = "");

		TonbPartTreeWidgetItem(const TonbPartTreeWidgetItem&);

	public slots:

		void RenameItemSlot();

	};
}

#endif // !_TonbPartTreeWidgetItem_Header
