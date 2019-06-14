#pragma once
#ifndef _TonbDisplacementTWI_Header
#define _TonbDisplacementTWI_Header

#include <TonbTWI.hxx>

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

	class TonbDisplacementTWI
		: public TonbTWI
	{

		Q_OBJECT

		struct DisplacementContextMenu
		{
			QAction* theRenameAction_ = NULL;

			QAction* theNewGeometryPartAction_ = NULL;
		};

	private:

		std::shared_ptr<DisplacementContextMenu> theContextMenu_ = NULL;

		std::shared_ptr<Model_Entity> theHull_;
		//DispNo1_HullPatch* theHull_ = NULL;

		bool theSymmetry_;

		void CreateMenu();

		void CreateProperties();

	public:

		TonbDisplacementTWI(SimulationWindow* parentwindow = 0, TonbTWI* parent = 0, const QString& title = "");

		void CreateHull(bool Symmetry = false);

		std::shared_ptr<Model_Entity> GetHull() const
		{
			return theHull_;
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

#endif // !_TonbDisplacementTWI_Header
