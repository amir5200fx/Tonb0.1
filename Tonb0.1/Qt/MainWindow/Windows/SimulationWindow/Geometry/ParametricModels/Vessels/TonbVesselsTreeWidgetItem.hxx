#pragma once
#ifndef _TonbVesselsTreeWidgetItem_Header
#define _TonbVesselsTreeWidgetItem_Header

#include <TonbTreeWidgetItem.hxx>
#include <QtCore/qobject.h>

namespace AutLib
{

	class TonbDisplacementTreeWidgetItem;
	class Vessel_NewWindow;

	class TonbVesselsTreeWidgetItem
		: public QObject
		, public TonbTreeWidgetItem
	{

		Q_OBJECT

		struct VesselContextMenu
		{
			QAction* theNewAction_ = NULL;
		};

	private:

		TonbDisplacementTreeWidgetItem* theDisplacementItem_ = NULL;

		VesselContextMenu* theContextMenu_ = NULL;

		Vessel_NewWindow* theNewWindow_ = NULL;

	public:

		TonbVesselsTreeWidgetItem(QWidget* parentwindow = 0, TonbTreeWidgetItem* parent = 0, const QString& title = "");

		void DeleteNewWindow(int result);

		TonbDisplacementTreeWidgetItem* GetDisplacementTreeWidgetItem() const
		{
			return theDisplacementItem_;
		}

		TonbDisplacementTreeWidgetItem*& GetDisplacementTreeWidgetItem()
		{
			return theDisplacementItem_;
		}

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
