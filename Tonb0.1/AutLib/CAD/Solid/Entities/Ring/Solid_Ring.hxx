#pragma once
#ifndef _Solid_Ring_Header
#define _Solid_Ring_Header

#include <Solid_Edge.hxx>

namespace AutLib
{

	class Solid_Ring
		: public Solid_Edge
	{

		/*Private Data*/

	public:

		Solid_Ring
		(
			const Standard_Integer theIndex,
			const word& theName,
			const vertex_ptr& theVtx,
			const curve_ptr& theCurve,
			const Standard_Boolean theSense = Standard_True
		)
			: Solid_Edge(theIndex, theName, theVtx, theVtx, theCurve, theSense)
		{}

		Solid_Ring
		(
			const Standard_Integer theIndex,
			const vertex_ptr& theVtx,
			const curve_ptr& theCurve,
			const Standard_Boolean theSense = Standard_True
		)
			: Solid_Edge(theIndex, theVtx, theVtx, theCurve, theSense)
		{}

		Solid_Ring
		(
			const vertex_ptr& theVtx,
			const curve_ptr& theCurve,
			const Standard_Boolean theSense = Standard_True
		)
			: Solid_Edge(theVtx, theVtx, theCurve, theSense)
		{}

		/*Solid_Ring
		(
			const Standard_Integer theIndex,
			const word& theName,
			const curve_ptr& theCurve,
			const Standard_Boolean theSense = Standard_True
		)
			: Solid_Edge(theIndex, theName, theCurve, theSense)
		{}*/

		Solid_Ring
		(
			const Standard_Integer theIndex,
			const curve_ptr& theCurve,
			const Standard_Boolean theSense = Standard_True
		)
			: Solid_Edge(theIndex, theCurve, theSense)
		{}

		Solid_Ring
		(
			const curve_ptr& theCurve,
			const Standard_Boolean theSense = Standard_True
		)
			: Solid_Edge(theCurve, theSense)
		{}
	};
}

#endif // !_Solid_Ring_Header
