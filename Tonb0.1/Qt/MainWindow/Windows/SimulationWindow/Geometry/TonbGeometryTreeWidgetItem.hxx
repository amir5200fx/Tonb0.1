#pragma once
#ifndef _TonbGeometryTreeWidgetItem_Header
#define _TonbGeometryTreeWidgetItem_Header

#include <TonbTreeWidgetItem.hxx>

class QTreeWidget;

namespace AutLib
{

	class TonbParametricModelsTreeWidgetItem;

	class TonbGeometryTreeWidgetItem
		: public TonbTreeWidgetItem
	{

		TonbParametricModelsTreeWidgetItem* theParametricModelsItem_ = NULL;

	public:

		TonbGeometryTreeWidgetItem(QWidget* windowparent = 0, QTreeWidget* parent = 0, const QString& title = "");
	};
}

#endif // !_TonbGeometryTreeWidgetItem_Header
