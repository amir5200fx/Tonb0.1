#include <iostream>

#include <Smart_Variable.hxx>
#include <UnitSystem.hxx>

#include <OFstream.hxx>
#include <Vessels_DispNo1.hxx>

using namespace AutLib;


int main()
{
	/*Smart_Variable<scalar, DynViscosityUnitExps> real("dynamic viscosity of water", 0.001, UnitSystem_DynViscosity_NSecPerSquareMeter);

	fileName name = "out.txt";
	OFstream out(name);
	out << real << endl;*/

	DispNo1_BareHull patch;
	patch.Perform();
	patch.Discrete();
	patch.ExportToFile();

	PAUSE;
	return 0;

	std::cout << Convertor::Pressure<UnitSystem_Pressure_atm, UnitSystem_Pressure_psi>::value << std::endl;
	std::cout << ConvertorTables::Length[UnitSystem_Length_cm][UnitSystem_Length_km] << std::endl;
	std::cout << ConvertorTables::Velocity[UnitSystem_Velocity_kn][UnitSystem_Velocity_mPerSec] << std::endl;

	std::cout << ConvertUnit(UnitSystem_Acceleration_ftPerSecPerSec, UnitSystem_Acceleration_mPerSecPerSec) << std::endl;

	system("pause");
}