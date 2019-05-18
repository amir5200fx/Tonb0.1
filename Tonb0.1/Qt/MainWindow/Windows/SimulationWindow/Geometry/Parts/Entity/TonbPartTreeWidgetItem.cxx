#include <TonbPartTreeWidgetItem.hxx>
#include <TonbSimulationTreeWidget.hxx>
#include <TonbScenesTreeWidgetItem.hxx>
#include <TonbSceneItem.hxx>
#include <qttreepropertybrowser.h>
#include <QtWidgets/qfiledialog.h>
#include <QtWidgets/qmessagebox.h>
#include <TonbDisplacementTreeWidgetItem.hxx>
#include <Cad3d_Solid.hxx>
#include <Model_Entity.hxx>
#include <Model_Box.hxx>
#include <Cad3d_SolidTools.hxx>

AutLib::TonbPartTreeWidgetItem::TonbPart::TonbPart(std::shared_ptr<Model_Entity> model)
	: thePartEntity_(model)
{
	thePartSolid_ = std::make_shared<Cad3d_Solid>(Cad3d_SolidTools::GetSurfaces(model->GetEntity()));
	thePartSolid_->SetName(model->Name());
}

AutLib::TonbPartTreeWidgetItem::TonbPartTreeWidgetItem(SimulationWindow * parentwindow, TonbTreeWidgetItem * parent, const QString & title)
	: TonbTreeWidgetItem(parentwindow, parent, title)
{
	setIcon(0, QIcon(":/Images/Icons/Part/Part_Icon.png"));
	setFlags(flags() | Qt::ItemIsEditable);

	theContextMenu_ = new PartContextMenu;

	theContextMenu_->theRenameAction_ = new QAction("Rename", (QWidget*)this->GetParentWindow());
	theContextMenu_->theNewGeometryScene_ = new QAction("New Geometry Scene", (QWidget*)this->GetParentWindow());
	theContextMenu_->theExport_ = new QAction("Export", (QWidget*)this->GetParentWindow());
	theContextMenu_->theExport_->setIcon(QIcon(":/Menus/Icons/Menus/File/Export.png"));

	GetContextMenu()->addAction(theContextMenu_->theRenameAction_);
	GetContextMenu()->addAction(theContextMenu_->theNewGeometryScene_);
	GetContextMenu()->addAction(theContextMenu_->theExport_);

	QObject::connect(theContextMenu_->theRenameAction_, SIGNAL(triggered()), this, SLOT(RenameItemSlot()));
	QObject::connect(theContextMenu_->theNewGeometryScene_, SIGNAL(triggered()), this, SLOT(AddGeometrySceneSlot()));
	QObject::connect(theContextMenu_->theExport_, SIGNAL(triggered()), this, SLOT(ExportPartSlot()));

	this->FindProperty("Name")->property()->setEnabled(true);
}



AutLib::TonbPartTreeWidgetItem::TonbPartTreeWidgetItem(const TonbPartTreeWidgetItem & part)
	: TonbTreeWidgetItem(part.GetParentWindow(), part.GetParentItem(), part.text(0))
{
	setIcon(0, QIcon(":/Images/Icons/Part/Part_Icon.png"));
}

//void AutLib::TonbPartTreeWidgetItem::RenameItemSlot()
//{
//	GetParentView()->editItem(this);
//}

void AutLib::TonbPartTreeWidgetItem::AddGeometrySceneSlot()
{
	this->GetParentView()->GetScenesItem()->AddScene(this);

	this->setSelected(false);

	emit this->GetParentView()->expandItem(this->GetParentView()->GetScenesItem()->GetScenes().last()->GetParentItem());
	this->GetParentView()->GetScenesItem()->GetScenes().last()->setSelected(true);
	emit this->GetParentView()->itemClicked(this->GetParentView()->GetScenesItem()->GetScenes().last(), 0);
}

void AutLib::TonbPartTreeWidgetItem::ExportPartSlot()
{
	QList<QString> QfileTypes;
	QfileTypes.push_back("IGES (*.igs)");
	QfileTypes.push_back("STEP (*.stp; *.step)");
	QfileTypes.push_back("Tecplot (*.plt)");

	QString fileTypes;
	for (int i = 0; i < QfileTypes.size() - 1; i++)
	{
		fileTypes += QfileTypes.at(i);
		fileTypes += ";;";
	}
	fileTypes += QfileTypes.at(QfileTypes.size() - 1);

	QString* ext = new QString("IGES");
	QString fileName = QFileDialog::getSaveFileName((QWidget*)this->GetParentWindow(),
		tr("Export Part"), "",
		fileTypes, ext);

	if (fileName.isEmpty())
		return;
	else
	{
		thePartGeometry_->thePartEntity_->SetFileName(fileName.toStdString());
		if (*ext == "IGES (*.igs)")
		{
			thePartGeometry_->thePartEntity_->SetFileFromat(Io::EntityIO_Format_IGES);
			thePartGeometry_->thePartEntity_->ExportToFile();
		}
		else if (*ext == "STEP (*.stp; *.step)")
		{
			thePartGeometry_->thePartEntity_->SetFileFromat(Io::EntityIO_Format_STEP);
			thePartGeometry_->thePartEntity_->ExportToFile();
		}
		else if (*ext == "Tecplot (*.plt)")
		{
			thePartGeometry_->thePartEntity_->SetFileFromat(Io::EntityIO_Format_TecPlot);
			thePartGeometry_->thePartEntity_->ExportToFile();
		}
	}
}