#pragma once
#ifndef _TonbPartsTreeWidgetItem_Header
#define _TonbPartsTreeWidgetItem_Header

#include <TonbTreeWidgetItem.hxx>

namespace AutLib
{

	class TonbPartTreeWidgetItem;
	class TonbDisplacementTreeWidgetItem;
	class SimulationWindow;
	class Model_Entity;

	class TonbPartsTreeWidgetItem
		: public TonbTreeWidgetItem
	{

		Q_OBJECT

	private:

		struct PartsItemContextMenu
		{
			QMenu* theNewShapePart_ = NULL;

			QAction* theNewShapePartBlock_ = NULL;
			QAction* theNewShapePartCone_ = NULL;
			QAction* theNewShapePartCylinder_ = NULL;
			QAction* theNewShapePartSphere_ = NULL;
			QAction* theNewShapePartTorus_ = NULL;
		};

		QList<TonbPartTreeWidgetItem*> theParts_;

		PartsItemContextMenu* thePartsItemContextMenu_ = NULL;

		void CreateMenu();

	public:

		TonbPartsTreeWidgetItem(SimulationWindow* parentwindow = nullptr, TonbTreeWidgetItem* parent = nullptr, const QString& title = "Parts");

		int GetNumberOfParts() const
		{
			return theParts_.size();
		}

		TonbPartTreeWidgetItem* GetPart(const QString& partName) const;

		QList<TonbPartTreeWidgetItem*> GetParts() const
		{
			return theParts_;
		}

		QList<TonbPartTreeWidgetItem*>& GetParts()
		{
			return theParts_;
		}

		int GetPartIndex(const QString& partName) const;

		void AddPart(TonbPartTreeWidgetItem* part);

		void AddPart(TonbDisplacementTreeWidgetItem* item, const QString& text);

		void AddPart(TonbDisplacementTreeWidgetItem* item);

		void AddPart(std::shared_ptr<Model_Entity> part, const QString& name);

		void RemovePart(const QString& partName);

		void RemovePart(TonbPartTreeWidgetItem* part);

		void RemovePartAt(int Index);

	public slots:

		void AddBlock();

		void AddCone();

		void AddCylinder();

		void AddShpere();

		void AddTorus();

	};
}

#endif // !_TonbPartsTreeWidgetItem_Header
