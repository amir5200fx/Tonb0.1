#include <iostream>

#include <Smart_Variable.hxx>
#include <UnitSystem.hxx>

#include <OFstream.hxx>
#include <Vessels_DispNo1.hxx>

#include <QtWidgets\qapplication.h>
#include <QtWidgets\qlabel.h>

#include <Aft2d_Node.hxx>
#include <Aft2d_Edge.hxx>
#include <Mesh_ElementAdaptor.hxx>
#include <Geom_AdTree.hxx>
#include <Geom_PriorityList.hxx>
#include <Geom_AdTree.hxx>
#include <Aft_FrontGlobalData.hxx>
#include <AftSizeMap_Uniform.hxx>
#include <Aft_Core.hxx>
#include <Aft2d_FrontInfo.hxx>

#include <MainWindow.hxx>

using namespace AutLib;


int main(int argc, char *argv[])
{
	/*DispNo1_BareHull patch;
	patch.FwdFullness().Value() = 0.0;
	patch.AftFullness().Value() = 0.0;
	patch.Perform();
	patch.Discrete();
	patch.ExportToFile();*/

	//Aft2d_Node node(1, Pnt2d(0.3, -0.12));

	//Geom_AdTree<Aft2d_Node> tree;
	//Aft_FrontGlobalData<Aft2d_Edge, Geom_AdTree, Geom_PriorityList> front;

	//Mesh_ElementAdaptor<Aft2d_TriElement, 3> adaptor;
	//
	//AftSizeMap_Uniform<Aft2d_Edge> sizeMap(1.0);

	//QApplication app(argc, argv);
	//QLabel *label = new QLabel("Hello Qt!");
	//label->show();
	//return app.exec();

	auto sizeMap = std::make_shared<AftSizeMap_Uniform<Aft2d_Edge>>(0.1);
	Aft_Core<Aft2d_FrontInfo, Geom_AdTree, Geom_PriorityList, AftSizeMap_Uniform> core(sizeMap);

	QApplication app(argc, argv);
	MainWindow w;
	w.setMinimumSize(800, 600);
	w.showMaximized();

	return app.exec();
	/*PAUSE;
	return 0;*/

	
}