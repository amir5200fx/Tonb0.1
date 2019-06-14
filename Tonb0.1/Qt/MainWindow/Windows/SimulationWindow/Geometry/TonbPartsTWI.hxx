#pragma once
#ifndef _TonbPartsTWI_Header
#define _TonbPartsTWI_Header

#include <TonbTWI.hxx>

namespace AutLib
{

	class TonbPartTWI;
	class TonbDisplacementTWI;
	class SimulationWindow;
	class Model_Entity;

	class TonbPartsTWI
		: public TonbTWI
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

		QList<std::shared_ptr<TonbPartTWI>> theParts_;

		std::shared_ptr<PartsItemContextMenu> thePartsItemContextMenu_;

		void CreateMenu();

	public:

		TonbPartsTWI(SimulationWindow* parentwindow = nullptr, TonbTWI* parent = nullptr, const QString& title = "Parts");

		int GetNumberOfParts() const
		{
			return theParts_.size();
		}

		std::shared_ptr<TonbPartTWI> GetPart(const QString& partName) const;

		QList<std::shared_ptr<TonbPartTWI>> GetParts() const
		{
			return theParts_;
		}

		QList<std::shared_ptr<TonbPartTWI>>& GetParts()
		{
			return theParts_;
		}

		int GetPartIndex(const QString& partName) const;

		void AddPart(std::shared_ptr<TonbPartTWI> part);

		void AddPart(std::shared_ptr<TonbDisplacementTWI> item, const QString& text);

		void AddPart(std::shared_ptr<TonbDisplacementTWI> item);

		void AddPart(std::shared_ptr<Model_Entity> part, const QString& name);

		void RemovePart(const QString& partName);

		void RemovePart(std::shared_ptr<TonbPartTWI> part);

		void RemovePartAt(int Index);

	public slots:

		void AddBlock();

		void AddCone();

		void AddCylinder();

		void AddShpere();

		void AddTorus();

	};
}

#endif // !_TonbPartsTWI_Header
