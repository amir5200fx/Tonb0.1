#include <iostream>

#include <Smart_Variable.hxx>
#include <UnitSystem.hxx>

using namespace AutLib;


int main()
{

	//Smart_Variable<Standard_Real> real("x", dimless, 0.1);

	std::cout << Convertor::Pressure<UnitSystem_Pressure_atm, UnitSystem_Pressure_psi>::value << std::endl;
	std::cout << ConvertorTables::Length[UnitSystem_Length_cm][UnitSystem_Length_km] << std::endl;
	std::cout << ConvertorTables::Velocity[UnitSystem_Velocity_kn][UnitSystem_Velocity_mPerSec] << std::endl;

	std::cout << ConvertUnit(UnitSystem_Acceleration_ftPerSecPerSec, UnitSystem_Acceleration_mPerSecPerSec) << std::endl;

	system("pause");
}