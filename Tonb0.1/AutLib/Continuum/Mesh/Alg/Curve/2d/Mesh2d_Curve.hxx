#pragma once
#ifndef _Mesh2d_Curve_Header
#define _Mesh2d_Curve_Header

#include <Mesh_Curve.hxx>
#include <SizeMap2d.hxx>

//#include <Geom2d_Curve.hxx>
class Geom2d_Curve;

namespace AutLib
{

	typedef Mesh_Curve<Geom2d_Curve, SizeMap2d> Mesh2d_Curve;

	template<>
	void Mesh2d_Curve::ExportToPlt(OFstream& File) const;
}

#endif // !_Mesh2d_Curve_Header
