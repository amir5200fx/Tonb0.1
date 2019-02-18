#include <iostream>

#include <Smart_Variable.hxx>
#include <UnitSystem.hxx>

#include <OFstream.hxx>
#include <Vessels_DispNo1.hxx>

#include <QtWidgets\qapplication.h>
#include <QtWidgets\qlabel.h>

using namespace AutLib;


int main(int argc, char *argv[])
{
	/*DispNo1_BareHull patch;
	patch.FwdFullness().Value() = 0.0;
	patch.AftFullness().Value() = 0.0;
	patch.Perform();
	patch.Discrete();
	patch.ExportToFile();*/

	QApplication app(argc, argv);
	QLabel *label = new QLabel("Hello Qt!");
	label->show();
	return app.exec();

	/*PAUSE;
	return 0;*/

	
}