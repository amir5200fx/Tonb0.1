#pragma once
#include <OSstream.hxx>

namespace AutLib
{

	template<class Point>
	std::ostream& operator<<(std::ostream& os, const Entity_Box<Point>& b)
	{
		os
			<< " P0 = ("
			<< b.P0()
			<< "),  P1 = ("
			<< b.P1()
			<< ")";
	}

	template<class Point>
	Ostream & operator<<(Ostream & os, const Entity_Box<Point>& b)
	{
		os << " P0 = " << b.P0() << ", P1 = " << b.P1();
		os.check("Ostream & operator<<(Ostream & os, const Entity_Box<Point>& b)");
	}
}