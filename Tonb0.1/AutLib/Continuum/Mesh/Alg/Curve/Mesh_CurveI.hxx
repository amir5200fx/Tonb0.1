#pragma once
#include <Mesh_CurveLength.hxx>

template<class CurveEntity>
inline void AutLib::Mesh_Curve<CurveEntity>::Perform()
{
	const auto& Curve = theEntity_.Curve();

	// Determine the Length of the curve under the current space function
	auto CurveLength = Mesh_CurveLength<CurveEntity>::CalcLength(theEntity_, Tolerance());


}