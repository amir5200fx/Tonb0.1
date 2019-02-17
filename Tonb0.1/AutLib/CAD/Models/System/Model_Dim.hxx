#pragma once
#ifndef _Model_Dim_Header
#define _Model_Dim_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{

	namespace dimension
	{

		static constexpr Standard_Real MAX_DIM = (Standard_Real)500.0;
		static const Standard_Real MIN_DIM = (Standard_Real)0.;
		static const Standard_Real SMALL_TOL = (Standard_Real)0.01;
	}
}

#endif // !_Model_Dim_Header
