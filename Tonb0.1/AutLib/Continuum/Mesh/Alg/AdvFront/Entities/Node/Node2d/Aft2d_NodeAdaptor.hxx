#pragma once
#ifndef _Aft2d_NodeAdaptor_Header
#define _Aft2d_NodeAdaptor_Header

#include <Aft_NodeAdaptor.hxx>

namespace AutLib
{

	// Forward Declarations

	class Aft2d_Edge;
	class Aft2d_TriElement;

	typedef Aft_NodeAdaptor<Aft2d_Edge, Aft2d_TriElement, void> Aft2d_NodeAdaptor;
}

#endif // !_Aft2d_NodeAdaptor_Header
