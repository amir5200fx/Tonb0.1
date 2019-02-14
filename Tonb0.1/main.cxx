#include <iostream>

#include <Smart_Variable.hxx>
#include <UnitSystem.hxx>

using namespace AutLib;

int main()
{

	//Smart_Variable<Standard_Real> real("x", dimless, 0.1);

	std::cout << Convertor::Pressure<UnitSystem_Pressure_atm, UnitSystem_Pressure_psi>::value << std::endl;

	system("pause");
}