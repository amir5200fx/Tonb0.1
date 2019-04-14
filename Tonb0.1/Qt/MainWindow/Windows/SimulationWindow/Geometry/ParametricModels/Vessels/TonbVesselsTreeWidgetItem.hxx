#pragma once
#ifndef _TonbVesselsTreeWidgetItem_Header
#define _TonbVesselsTreeWidgetItem_Header

#include <TonbTreeWidgetItem.hxx>
#include <QtCore/qobject.h>

namespace AutLib
{

	class TonbDisplacementTreeWidgetItem;
	class Vessel_NewWindow;
	struct Page2Elements;

	class TonbVesselsTreeWidgetItem
		: public TonbTreeWidgetItem
	{

		Q_OBJECT

		struct VesselContextMenu
		{
			QAction* theNewAction_ = NULL;
		};

	private:

		QList<TonbDisplacementTreeWidgetItem*> theDisplacementItems_;

		VesselContextMenu* theContextMenu_ = NULL;

		Vessel_NewWindow* theNewWindow_ = NULL;

	public:

		TonbVesselsTreeWidgetItem(SimulationWindow* parentwindow = 0, TonbTreeWidgetItem* parent = 0, const QString& title = "");

		void DeleteNewWindow(int result, Page2Elements* page);

		TonbDisplacementTreeWidgetItem* GetDisplacement(const QString& dispName) const;

		Vessel_NewWindow* GetNewWindow() const
		{
			return theNewWindow_;
		}

		Vessel_NewWindow*& GetNewWindow()
		{
			return theNewWindow_;
		}

	public slots:

		void CreateNewVesselWindow();
	};
}

#endif // !_TonbVesselsTreeWidgetItem_Header
