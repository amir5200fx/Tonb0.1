#pragma once
#ifndef _Aft2d_EdgeAdaptor_Header
#define _Aft2d_EdgeAdaptor_Header

#include <Mesh_EdgeAdaptor.hxx>

namespace AutLib
{

	// Forward Declarations
	class Aft2d_TriElement;

	typedef Mesh_EdgeAdaptor<Aft2d_TriElement> Aft2d_EdgeAdaptor;
}

#endif // !_Aft2d_EdgeAdaptor_Header
