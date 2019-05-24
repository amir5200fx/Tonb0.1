#pragma once
#ifndef _TonbVesselsTWI_Header
#define _TonbVesselsTWI_Header

#include <TonbTWI.hxx>
#include <QtCore/qobject.h>

namespace AutLib
{

	class TonbDisplacementTWI;
	class Vessel_NewWindow;
	struct Page2Elements;

	class TonbVesselsTWI
		: public TonbTWI
	{

		Q_OBJECT

		struct VesselContextMenu
		{
			QAction* theNewAction_ = NULL;
		};

	private:

		QList<std::shared_ptr<TonbDisplacementTWI>> theDisplacementItems_;

		std::shared_ptr<VesselContextMenu> theContextMenu_ = NULL;

		std::shared_ptr<Vessel_NewWindow> theNewWindow_ = NULL;

	public:

		TonbVesselsTWI(SimulationWindow* parentwindow = 0, TonbTWI* parent = 0, const QString& title = "");

		void DeleteNewWindow(int result, Page2Elements* page);

		std::shared_ptr <TonbDisplacementTWI> GetDisplacement(const QString& dispName) const;

		std::shared_ptr<Vessel_NewWindow> GetNewWindow() const
		{
			return theNewWindow_;
		}

		std::shared_ptr<Vessel_NewWindow>& GetNewWindow()
		{
			return theNewWindow_;
		}

	public slots:

		void CreateNewVesselWindow();
	};
}

#endif // !_TonbVesselsTWI_Header
