#include <TonbDisplacementTreeWidgetItem.hxx>
#include <QtWidgets/qaction.h>
#include <QtWidgets/qmenu.h>

AutLib::TonbDisplacementTreeWidgetItem::TonbDisplacementTreeWidgetItem(QWidget* parentwindow, TonbTreeWidgetItem * parent, const QString & title)
	: TonbTreeWidgetItem(parentwindow, parent, title)
{
	setFlags(flags() | Qt::ItemIsEditable);

	theContextMenu_ = new DisplacementContextMenu;

	theContextMenu_->theRenameAction_ = new QAction("Rename", parentwindow);

	GetContextMenu()->addAction(theContextMenu_->theRenameAction_);

	QObject::connect(theContextMenu_->theRenameAction_, SIGNAL(triggered()), this, SLOT(RenameItem()));
}

void AutLib::TonbDisplacementTreeWidgetItem::RenameItem()
{
	GetParentView()->editItem(this);
}