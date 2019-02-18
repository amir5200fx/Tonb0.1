#pragma once
#ifndef _Aft2d_NodeAdaptorFwd_Header
#define _Aft2d_NodeAdaptorFwd_Header

namespace AutLib
{

	template<class EdgeType, class ElementType>
	class Aft_NodeAdaptor;

	// Forward Declarations

	class Aft2d_Edge;
	class Aft2d_TriElement;

	typedef Aft_NodeAdaptor<Aft2d_Edge, Aft2d_TriElement> Aft2d_NodeAdaptor;
}

#endif // !_Aft2d_NodeAdaptorFwd_Header
