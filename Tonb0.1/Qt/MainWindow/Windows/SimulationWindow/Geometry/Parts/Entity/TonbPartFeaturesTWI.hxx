#pragma once
#ifndef _TonbPartFeaturesTWI_Header
#define _TonbPartFeaturesTWI_Header

#include <TonbTWI.hxx>

class vtkActor;

namespace AutLib
{
	class Solid_Entity;
	class Model_Entity;

	class TonbPartFeaturesTWI : public TonbTWI
	{

		Q_OBJECT

	private:

		QList<std::shared_ptr<Solid_Entity>>theFeatures_;

		QList<std::shared_ptr<TonbTWI>> theFeaturesItem_;

	public:

		TonbPartFeaturesTWI
		(
			SimulationWindow* parentwindow = nullptr,
			TonbTWI* parent = nullptr,
			const QString& title = "",
			QList<std::shared_ptr<Solid_Entity>> features = QList<std::shared_ptr<Solid_Entity>>(),
			std::shared_ptr<Model_Entity> model = NULL
		);

	public slots:
		void SelectPartFeature(QTreeWidgetItem* item, int column);
	};
}

#endif // !_TonbPartFeaturesTWI_Header
