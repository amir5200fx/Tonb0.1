#pragma once
#ifndef _TonbPartTreeWidgetItem_Header
#define _TonbPartTreeWidgetItem_Header

#include <TonbTreeWidgetItem.hxx>

namespace AutLib
{

	class SimulationWindow;
	class TonbDisplacementTreeWidgetItem;

	class TonbPartTreeWidgetItem
		: public QObject
		, public TonbTreeWidgetItem
	{

		struct PartContextMenu
		{
			QAction* theRenameAction_ = NULL;

			QAction* theNewGeometryScene_ = NULL;
		};

		Q_OBJECT

	private:

		PartContextMenu* theContextMenu_ = NULL;

		TonbDisplacementTreeWidgetItem* theDispGeometry_ = NULL;

	public:

		TonbPartTreeWidgetItem(SimulationWindow* parentwindow = nullptr, TonbTreeWidgetItem* parent = nullptr, const QString& title = "");

		TonbPartTreeWidgetItem(const TonbPartTreeWidgetItem&);

		TonbDisplacementTreeWidgetItem* GetDisplacementGeometry() const
		{
			return theDispGeometry_;
		}

		TonbDisplacementTreeWidgetItem*& GetDisplacementGeometry()
		{
			return theDispGeometry_;
		}

	public slots:

		void RenameItemSlot();

		void AddGeometrySceneSlot();

	};
}

#endif // !_TonbPartTreeWidgetItem_Header
