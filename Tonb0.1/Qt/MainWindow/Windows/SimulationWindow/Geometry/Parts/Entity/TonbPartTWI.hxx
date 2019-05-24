#pragma once
#ifndef _TonbPartTWI_Header
#define _TonbPartTWI_Header

#include <TonbTWI.hxx>
#include <vtkSmartPointer.h>

class vtkActor;

namespace AutLib
{

	class SimulationWindow;
	//class TonbDisplacementTWI;
	class Cad3d_Solid;
	class Cad3d_SolidTools;
	class Model_Entity;
	class Solid_Paired;
	class Solid_Face;
	class Solid_Entity;

	class TonbPartFeaturesTWI;
	class TonbSceneItem;

	class TonbPartTWI
		: public TonbTWI
	{

	public:

		struct TonbPartData
		{
			TonbPartData(std::shared_ptr<Solid_Entity> data);
			std::shared_ptr<Solid_Entity> theData_ = NULL;
			vtkSmartPointer<vtkActor> thePointerToActor_;
			std::shared_ptr<TonbTWI> thePointerToItem_ = NULL;
		};

		struct TonbPart
		{
			TonbPart(std::shared_ptr<Model_Entity> model, std::shared_ptr<TonbTWI> theParent = NULL);
			TonbPart() {};

			std::shared_ptr<Cad3d_Solid> thePartSolid_ = NULL;
			std::shared_ptr<Model_Entity> thePartEntity_ = NULL;

			QList<std::shared_ptr<TonbPartData>> theEdges_;
			QList<std::shared_ptr<TonbPartData>> theFaces_;

			std::shared_ptr<TonbTWI> theParent_ = NULL;

			std::shared_ptr<TonbSceneItem> thePointerToScene_ = NULL;
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

		std::shared_ptr<PartContextMenu> theContextMenu_ = NULL;

		std::shared_ptr<TonbPart> thePartGeometry_ = NULL;

		QList<std::shared_ptr<TonbPartFeaturesTWI>> theFeatures_;

	public:

		TonbPartTWI(SimulationWindow* parentwindow = nullptr, TonbTWI* parent = nullptr, const QString& title = "");

		TonbPartTWI(const TonbPartTWI&);

		void CreateFeatures(QList<std::shared_ptr<Solid_Entity>> features, std::shared_ptr<Model_Entity> model);

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

#endif // !_TonbPartTWI_Header