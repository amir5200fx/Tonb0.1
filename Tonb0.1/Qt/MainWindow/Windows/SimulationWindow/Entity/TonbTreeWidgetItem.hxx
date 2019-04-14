#pragma once
#ifndef _TonbTreeWidgetItem_Header
#define _TonbTreeWidgetItem_Header

#include <QtWidgets/qtreewidget.h>
#include <QtCore/QObject>

class QtTreePropertyBrowser;
class QtVariantPropertyManager;
class QtVariantEditorFactory;
class QtBrowserItem;
class QtProperty;
class QVariant;

namespace AutLib
{

	class TonbSimulationTreeWidget;
	class SimulationWindow;

	class TonbTreeWidgetItem
		: public QObject
		, public QTreeWidgetItem
	{

		Q_OBJECT

		QMenu* theMenu_ = NULL;

		SimulationWindow* theParentWindow_ = NULL;

		TonbTreeWidgetItem* theParentItem_ = NULL;

		TonbSimulationTreeWidget* theParentView_ = NULL;

		QtTreePropertyBrowser* theProperty_ = NULL;
		QtVariantPropertyManager* theVariantManager_ = NULL;
		QtVariantEditorFactory* theVriantFactory_ = NULL;

	public:

		TonbTreeWidgetItem(SimulationWindow* parentwindow = 0, TonbSimulationTreeWidget* parent = 0, const QString& title = "");

		TonbTreeWidgetItem(SimulationWindow* parentwindow = 0, TonbTreeWidgetItem* parent = 0, const QString& title = "");

		void CreateProperty();

		QMenu* GetContextMenu() const
		{
			return theMenu_;
		}

		QMenu*& GetContextMenu()
		{
			return theMenu_;
		}

		SimulationWindow* GetParentWindow() const
		{
			return theParentWindow_;
		}

		SimulationWindow*& GetParentWindow()
		{
			return theParentWindow_;
		}

		TonbTreeWidgetItem* GetParentItem() const
		{
			return theParentItem_;
		}

		TonbTreeWidgetItem*& GetParentItem()
		{
			return theParentItem_;
		}

		TonbSimulationTreeWidget* GetParentView() const
		{
			return theParentView_;
		}

		TonbSimulationTreeWidget*& GetParentView()
		{
			return theParentView_;
		}

		QtTreePropertyBrowser* GetProperty() const
		{
			return theProperty_;
		}

		QtTreePropertyBrowser*& GetProperty()
		{
			return theProperty_;
		}

		QtVariantPropertyManager* GetVariantPropertyManager() const
		{
			return theVariantManager_;
		}

		QtVariantPropertyManager*& GetVariantPropertyManager()
		{
			return theVariantManager_;
		}

		QtVariantEditorFactory* GetVariantEditorFactory() const
		{
			return theVriantFactory_;
		}

		QtVariantEditorFactory*& GetVariantEditorFactory()
		{
			return theVriantFactory_;
		}

		QtBrowserItem* FindProperty(QtBrowserItem* property, const QString& IdName);

		QtBrowserItem* FindProperty(const QString& IdName);

	public slots:

		void RenameItemSlot();

		virtual void PropertyChangedSlot(QtProperty * property, const QVariant & val);

		virtual void SnapshotSlot() {};

		virtual void onCustomContextMenuRequested(const QPoint& pos) {};

		virtual void HideObjectSlot() {};

		virtual void ShowAllObjectSlot() {};
	};
}

#endif // !_TonbTreeWidgetItem_Header
