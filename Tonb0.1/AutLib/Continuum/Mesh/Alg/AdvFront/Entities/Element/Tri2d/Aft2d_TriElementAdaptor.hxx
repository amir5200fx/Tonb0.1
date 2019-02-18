#pragma once
#ifndef _Aft2d_TriElementAdaptor_Header
#define _Aft2d_TriElementAdaptor_Header

#include <Mesh_ElementAdaptor.hxx>

namespace AutLib
{

	// Forward Declarations
	class Aft2d_TriElement;

	typedef Mesh_ElementAdaptor<Aft2d_TriElement, 3> Aft2d_TriElementAdaptor;
}

#endif // !_Aft2d_TriElementAdaptor_Header
