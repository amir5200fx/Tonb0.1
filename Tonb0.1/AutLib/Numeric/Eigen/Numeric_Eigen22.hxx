#pragma once
#ifndef _Numeric_Eigen22_Header
#define _Numeric_Eigen22_Header

#include <Standard_TypeDef.hxx>
#include <math.h>

namespace AutLib
{

	class Numeric_Eigen22
	{

	public:

		static void CalcEigen
		(
			const Standard_Real A[2][2],
			Standard_Real eVals[2],
			Standard_Real eVecs[2][2],
			const Standard_Real Zero = 1.0E-6
		)
		{
			auto T = A[0][0] + A[1][1];
			auto D = A[0][0] * A[1][1] - A[1][0] * A[0][1];

			auto SQ = sqrt(T*T*(Standard_Real)0.25 - D);

			T *= (Standard_Real)0.5;

			eVals[0] = T + SQ;
			eVals[1] = T - SQ;

			if (abs(A[1][0]) > Zero)
			{
				eVecs[0][0] = eVals[0] - A[1][1];
				eVecs[1][0] = A[1][0];

				eVecs[0][1] = eVals[1] - A[1][1];
				eVecs[1][1] = A[1][0];
			}
			else if (abs(A[0][1]) > Zero)
			{
				eVecs[0][0] = A[0][1];
				eVecs[1][0] = eVals[0] - A[0][0];

				eVecs[0][1] = A[0][1];
				eVecs[1][1] = eVals[1] - A[0][0];
			}
			else
			{
				eVecs[0][0] = (Standard_Real)1.0;
				eVecs[1][0] = (Standard_Real)0.0;

				eVecs[0][1] = (Standard_Real)0.0;
				eVecs[1][1] = (Standard_Real)1.0;
			}
		}

		static void CalcEigen_Normalized
		(
			const Standard_Real A[2][2],
			Standard_Real eVals[2],
			Standard_Real eVecs[2][2],
			const Standard_Real Zero = 1.0E-6
		)
		{
			auto T = A[0][0] + A[1][1];
			auto D = A[0][0] * A[1][1] - A[1][0] * A[0][1];

			auto SQ = sqrt(T*T*(Standard_Real)0.25 - D);

			T *= (Standard_Real)0.5;

			eVals[0] = T + SQ;
			eVals[1] = T - SQ;

			if (abs(A[1][0]) > Zero)
			{
				eVecs[0][0] = eVals[0] - A[1][1];
				eVecs[1][0] = A[1][0];

				auto d = sqrt(eVecs[0][0] * eVecs[0][0] + eVecs[1][0] * eVecs[1][0]);

				eVecs[0][0] /= d;
				eVecs[1][0] /= d;

				eVecs[0][1] = eVals[1] - A[1][1];
				eVecs[1][1] = A[1][0];

				d = sqrt(eVecs[0][1] * eVecs[0][1] + eVecs[1][1] * eVecs[1][1]);

				eVecs[0][1] /= d;
				eVecs[1][1] /= d;
			}
			else if (abs(A[0][1]) > Zero)
			{
				eVecs[0][0] = A[0][1];
				eVecs[1][0] = eVals[0] - A[0][0];

				auto d = sqrt(eVecs[0][0] * eVecs[0][0] + eVecs[1][0] * eVecs[1][0]);

				eVecs[0][0] /= d;
				eVecs[1][0] /= d;

				eVecs[0][1] = A[0][1];
				eVecs[1][1] = eVals[1] - A[0][0];

				d = sqrt(eVecs[0][1] * eVecs[0][1] + eVecs[1][1] * eVecs[1][1]);

				eVecs[0][1] /= d;
				eVecs[1][1] /= d;
			}
			else
			{
				eVecs[0][0] = (Standard_Real)1.0;
				eVecs[1][0] = (Standard_Real)0.0;

				eVecs[0][1] = (Standard_Real)0.0;
				eVecs[1][1] = (Standard_Real)1.0;
			}
		}
	};
}

#endif // !_Numeric_Eigen22_Header
