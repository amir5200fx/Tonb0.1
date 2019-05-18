#pragma once
#ifndef _TonbPartTreeWidgetItem_Header
#define _TonbPartTreeWidgetItem_Header

#include <TonbTreeWidgetItem.hxx>

namespace AutLib
{

	class SimulationWindow;
	//class TonbDisplacementTreeWidgetItem;
	class Cad3d_Solid;
	class Cad3d_SolidTools;
	class Model_Entity;

	class TonbPartTreeWidgetItem
		: public TonbTreeWidgetItem
	{

	public:

		struct TonbPart
		{
			TonbPart(std::shared_ptr<Model_Entity> model);

			std::shared_ptr<Cad3d_Solid> thePartSolid_ = NULL;
			std::shared_ptr<Model_Entity> thePartEntity_ = NULL;
		};

	private:

		struct PartContextMenu
		{
			QAction* theRenameAction_ = NULL;

			QAction* theNewGeometryScene_ = NULL;

			QAction* theExport_ = NULL;
		};

		Q_OBJECT

	private:

		PartContextMenu* theContextMenu_ = NULL;

		std::shared_ptr<TonbPart> thePartGeometry_ = NULL;

	public:

		TonbPartTreeWidgetItem(SimulationWindow* parentwindow = nullptr, TonbTreeWidgetItem* parent = nullptr, const QString& title = "");

		TonbPartTreeWidgetItem(const TonbPartTreeWidgetItem&);

		std::shared_ptr<TonbPart> GetPartGeometry() const
		{
			return thePartGeometry_;
		}

		std::shared_ptr<TonbPart>& GetPartGeometry()
		{
			return thePartGeometry_;
		}

	public slots:

		//void RenameItemSlot();

		void AddGeometrySceneSlot();

		void ExportPartSlot();

	};
}

#endif // !_TonbPartTreeWidgetItem_Header