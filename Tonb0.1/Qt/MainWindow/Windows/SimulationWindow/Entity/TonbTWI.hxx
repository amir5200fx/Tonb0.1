#pragma once
#ifndef _TonbTWI_Header
#define _TonbTWI_Header

#include <QtWidgets/qtreewidget.h>
#include <QtCore/QObject>
#include <TonbGlobals.hxx>

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

	class TonbTWI
		: public QObject
		, public QTreeWidgetItem
		, public std::enable_shared_from_this<TonbTWI>
	{

		Q_OBJECT

		QMenu* theContextMenu_ = nullptr;

		SimulationWindow* theParentWindow_ = nullptr;

		TonbTWI* theParentItem_ = nullptr;

		TonbSimulationTreeWidget* theParentView_ = nullptr;

		std::shared_ptr<QtTreePropertyBrowser> theProperty_;
		std::shared_ptr<QtVariantPropertyManager> theVariantPropertyManager_;
		std::shared_ptr<QtVariantEditorFactory> theVariantEditorFactory_;

	public:

		TonbTWI(SimulationWindow* parentwindow = 0, TonbSimulationTreeWidget* parent = 0, const QString& title = "");

		TonbTWI(SimulationWindow* parentwindow = 0, TonbTWI* parent = 0, const QString& title = "");

		void CreateProperty();
		
		QMenu* GetContextMenu() const
		{
			return theContextMenu_;
		}

		QMenu*& GetContextMenu()
		{
			return theContextMenu_;
		}

		SimulationWindow* GetParentWindow() const
		{
			return theParentWindow_;
		}
		
		SimulationWindow*& GetParentWindow()
		{
			return theParentWindow_;
		}

		TonbTWI* GetParentItem() const
		{
			return theParentItem_;
		}

		TonbTWI*& GetParentItem()
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

		std::shared_ptr<QtTreePropertyBrowser> GetProperty() const
		{
			return theProperty_;
		}

		std::shared_ptr<QtTreePropertyBrowser>& GetProperty()
		{
			return theProperty_;
		}

		std::shared_ptr<QtVariantPropertyManager> GetVariantPropertyManager() const
		{
			return theVariantPropertyManager_;
		}

		std::shared_ptr<QtVariantPropertyManager>& GetVariantPropertyManager()
		{
			return theVariantPropertyManager_;
		}

		std::shared_ptr<QtVariantEditorFactory> GetVariantEditorFactory() const
		{
			return theVariantEditorFactory_;
		}

		std::shared_ptr<QtVariantEditorFactory>& GetVariantEditorFactory()
		{
			return theVariantEditorFactory_;
		}

		QtBrowserItem* FindProperty(QtBrowserItem* property, const QString& IdName);

		QtBrowserItem* FindProperty(const QString& IdName);

		static QString CorrectName(TonbTWI* parentItem, const QString& name);

	public slots:

		virtual void RenameItemSlot();

		virtual void PropertyChangedSlot(QtProperty * property, const QVariant & val);

		virtual void SnapshotSlot() {};

		virtual void onCustomContextMenuRequested(const QPoint& pos) {};

		virtual void HideObjectSlot() {};

		virtual void ShowAllObjectSlot() {};

		virtual void UpdateGeometryColorSlot(QtProperty * property, const QVariant & val) {};

		virtual void SelectPartFeature(QTreeWidgetItem *, int) {};

		virtual void onDoubleClickSlot(QTreeWidgetItem*, int) {};
	};
}

#endif // !_TonbTWI_Header
