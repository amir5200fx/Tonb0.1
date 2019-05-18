#pragma once
#ifndef _Solid_parEdge_Header
#define _Solid_parEdge_Header

#include <Solid_Entity.hxx>

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class Solid_parCurve;
	class Solid_parWire;

	class Solid_parEdge
		: public Solid_Entity
		, public std::enable_shared_from_this<Solid_parEdge>
	{

		typedef std::shared_ptr<Solid_parCurve> curve_ptr;
		typedef std::weak_ptr<Solid_parWire> wire_weak;

		/*Private Data*/

		curve_ptr theCurve_;

		wire_weak theWire_;

	public:

		typedef Solid_parCurve curveType;

		Solid_parEdge(const curve_ptr& theCurve)
			: theCurve_(theCurve)
		{}

		Solid_parEdge
		(
			const Standard_Integer theIndex,
			const curve_ptr& theCurve
		)
			: Solid_Entity(theIndex)
			, theCurve_(theCurve)
		{}

		Solid_parEdge
		(
			const Standard_Integer theIndex,
			const word& theName,
			const curve_ptr& theCurve
		)
			: Solid_Entity(theIndex, theName)
			, theCurve_(theCurve)
		{}

		Standard_Boolean IsRing() const;

		const curve_ptr& Curve() const
		{
			return theCurve_;
		}

		const wire_weak& Wire() const
		{
			return theWire_;
		}

		void SetWire(const wire_weak& theWire)
		{
			theWire_ = theWire;
		}
	};
}

#endif // !_Solid_parEdge_Header
