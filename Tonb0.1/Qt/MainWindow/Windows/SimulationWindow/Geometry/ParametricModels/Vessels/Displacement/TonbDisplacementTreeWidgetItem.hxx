#pragma once
#ifndef _TonbDisplacementTreeWidgetItem_Header
#define _TonbDisplacementTreeWidgetItem_Header

#include <TonbTreeWidgetItem.hxx>
#include <QtCore/qobject.h>

namespace AutLib
{

	class TonbDisplacementTreeWidgetItem
		: public QObject
		, public TonbTreeWidgetItem
	{

		Q_OBJECT

		struct DisplacementContextMenu
		{
			QAction* theRenameAction_ = NULL;
		};

	private:

		DisplacementContextMenu* theContextMenu_ = NULL;

	public:

		TonbDisplacementTreeWidgetItem(QWidget* parentwindow = 0, TonbTreeWidgetItem* parent = 0, const QString& title = "");

	public slots:

		void RenameItem();
	};
}

#endif // !_TonbDisplacementTreeWidgetItem_Header
