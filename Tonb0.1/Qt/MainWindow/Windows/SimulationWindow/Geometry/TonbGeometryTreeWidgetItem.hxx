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

		TonbParametricModelsTreeWidgetItem* GetParametricModelsTreeWidgetItem() const
		{
			return theParametricModelsItem_;
		}

		TonbParametricModelsTreeWidgetItem*& GetParametricModelsTreeWidgetItem()
		{
			return theParametricModelsItem_;
		}
	};
}

#endif // !_TonbGeometryTreeWidgetItem_Header
