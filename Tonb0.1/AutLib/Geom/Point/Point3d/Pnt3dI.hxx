#pragma once
namespace AutLib
{

	inline Pnt3d operator+(const Pnt3d& P1, const Pnt3d& P2)
	{
		Pnt3d Temp = P1;
		Temp += P2;
		MOVE(Temp);
	}

	inline Pnt3d operator-(const Pnt3d& P1, const Pnt3d& P2)
	{
		Pnt3d Temp = P1;
		Temp -= P2;
		MOVE(Temp);
	}

	inline Pnt3d operator+(const Pnt3d& P1, const Standard_Real Scalar)
	{
		Pnt3d Temp = P1;
		Temp += Scalar;
		MOVE(Temp);
	}

	inline Pnt3d operator+(const Standard_Real Scalar, const Pnt3d& P1)
	{
		Pnt3d Temp = P1;
		Temp += Scalar;
		MOVE(Temp);
	}

	inline Pnt3d operator-(const Pnt3d& P1, const Standard_Real Scalar)
	{
		Pnt3d Temp = P1;
		Temp -= Scalar;
		MOVE(Temp);
	}

	inline Pnt3d operator*(const Pnt3d& P1, const Standard_Real Scalar)
	{
		Pnt3d Temp = P1;
		Temp *= Scalar;
		MOVE(Temp);
	}

	inline Pnt3d operator*(const Standard_Real Scalar, const Pnt3d& P1)
	{
		Pnt3d Temp = P1;
		Temp *= Scalar;
		MOVE(Temp);
	}

	inline Pnt3d operator/(const Pnt3d& P1, const Standard_Real Scalar)
	{
		Pnt3d Temp = P1;
		Temp /= Scalar;
		MOVE(Temp);
	}

	inline Standard_Real Distance(const Pnt3d& P1, const Pnt3d& P2)
	{
		return P1.Distance(P2);
	}

	inline Standard_Real SquareDistance(const Pnt3d& P1, const Pnt3d& P2)
	{
		return P1.SquareDistance(P2);
	}
}