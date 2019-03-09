#pragma once
#ifndef _TonbDisplacementTreeWidgetItem_Header
#define _TonbDisplacementTreeWidgetItem_Header

#include <TonbTreeWidgetItem.hxx>
#include <QtCore/qobject.h>

#include <memory>

class TopoDS_Shape;

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
		//DispNo1_HullPatch* theHull_ = NULL;

		bool theSymmetry_;

		void CreateMenu();

	public:

		TonbDisplacementTreeWidgetItem(SimulationWindow* parentwindow = 0, TonbTreeWidgetItem* parent = 0, const QString& title = "");

		void CreateHull(bool Symmetry = false);

		std::shared_ptr<DispNo1_HullPatch> GetHull() const
		{
			return std::move(theHull_);
		}

		std::shared_ptr<DispNo1_HullPatch>& GetHull()
		{
			return theHull_;
		}

		/*DispNo1_HullPatch* GetHull() const
		{
			return theHull_;
		}

		DispNo1_HullPatch*& GetHull()
		{
			return theHull_;
		}*/

		void DiscreteHull();

		const TopoDS_Shape& GetHullEntity() const;

		//TopoDS_Shape& GetHullEntity();

	public slots:

		void RenameItemSlot();

		void NewGeometryPartSlot();
	};
}

#endif // !_TonbDisplacementTreeWidgetItem_Header
