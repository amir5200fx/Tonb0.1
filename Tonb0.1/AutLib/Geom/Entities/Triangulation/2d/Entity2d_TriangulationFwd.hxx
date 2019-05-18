#pragma once
#ifndef _Entity2d_TriangulationFwd_Header
#define _Entity2d_TriangulationFwd_Header

#include <Pnt2d.hxx>
#include <Entity_Connectivity.hxx>

namespace AutLib
{

	// Forward Declarations
	template<class Point, class Connectivity, bool NeighbData>
	class Entity_StaticData;

	typedef Entity_StaticData<Pnt2d, connectivity::triple, false>
		Entity2d_Triangulation;
}

#endif // !_Entity2d_TriangulationFwd_Header
