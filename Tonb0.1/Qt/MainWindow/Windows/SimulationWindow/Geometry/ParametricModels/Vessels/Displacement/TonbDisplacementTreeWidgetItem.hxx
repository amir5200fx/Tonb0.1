#pragma once
#ifndef _TonbDisplacementTreeWidgetItem_Header
#define _TonbDisplacementTreeWidgetItem_Header

#include <TonbTreeWidgetItem.hxx>
#include <QtCore/qobject.h>

#include <memory>

namespace AutLib
{

	class DispNo1_HullPatch;

	class TonbDisplacementTreeWidgetItem
		: public QObject
		, public TonbTreeWidgetItem
	{

		Q_OBJECT

		struct DisplacementContextMenu
		{
			QAction* theRenameAction_ = NULL;

			QAction* theNewGeometryPartAction_ = NULL;
		};

	private:

		DisplacementContextMenu* theContextMenu_ = NULL;

		std::shared_ptr<DispNo1_HullPatch> theHull_;

		bool theSymmetry_;

		void CreateMenu();

	public:

		TonbDisplacementTreeWidgetItem(SimulationWindow* parentwindow = 0, TonbTreeWidgetItem* parent = 0, const QString& title = "");

		void CreateHull(bool Symmetry = false);

	public slots:

		void RenameItemSlot();

		void NewGeometryPartSlot();
	};
}

#endif // !_TonbDisplacementTreeWidgetItem_Header
