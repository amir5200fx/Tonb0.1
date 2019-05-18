#pragma once
#ifndef _TonbDisplacementTreeWidgetItem_Header
#define _TonbDisplacementTreeWidgetItem_Header

#include <TonbTreeWidgetItem.hxx>

#include <memory>

class TopoDS_Shape;
class QtProperty;
class QVariant;

namespace AutLib
{

	namespace Io
	{
		enum EntityIO_Format;
	}

	class DispNo1_HullPatch;
	class Model_Entity;

	class TonbDisplacementTreeWidgetItem
		: public TonbTreeWidgetItem
	{

		Q_OBJECT

		struct DisplacementContextMenu
		{
			QAction* theRenameAction_ = NULL;

			QAction* theNewGeometryPartAction_ = NULL;
		};

	private:

		DisplacementContextMenu* theContextMenu_ = NULL;

		std::shared_ptr<Model_Entity> theHull_;
		//DispNo1_HullPatch* theHull_ = NULL;

		bool theSymmetry_;

		void CreateMenu();

		void CreateProperties();

	public:

		TonbDisplacementTreeWidgetItem(SimulationWindow* parentwindow = 0, TonbTreeWidgetItem* parent = 0, const QString& title = "");

		void CreateHull(bool Symmetry = false);

		std::shared_ptr<Model_Entity> GetHull() const
		{
			return std::move(theHull_);
		}

		std::shared_ptr<Model_Entity>& GetHull()
		{
			return theHull_;
		}

		void ExportToFile(const QString& fileName, Io::EntityIO_Format format);

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

		//void RenameItemSlot();

		void NewGeometryPartSlot();

		void PropertyChangedSlot(QtProperty * property, const QVariant & val) override;
	};
}

#endif // !_TonbDisplacementTreeWidgetItem_Header
