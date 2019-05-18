#pragma once
#ifndef _Solid_Plane_Header
#define _Solid_Plane_Header

#include <Solid_Entity.hxx>

#include <memory>
#include <vector>

namespace AutLib
{

	// Forward Declarations
	class Solid_parWire;
	class Solid_parEdge;
	class Solid_Face;

	class Solid_Plane
		: public Global_Indexed
		, public Global_Named
		, public std::enable_shared_from_this<Solid_Plane>
	{

		typedef std::shared_ptr<Solid_parWire> wire_ptr;
		typedef std::vector<wire_ptr> wireList;
		typedef std::shared_ptr<wireList> wireList_ptr;

		typedef wire_ptr outer;
		typedef wireList_ptr inner;

		/*Private Data*/

		outer theOutter_;
		inner theInner_;

	public:

		typedef Solid_parWire wireType;
		typedef Solid_parEdge edgeType;

		Solid_Plane
		(
			const Standard_Integer theIndex,
			const word& theName,
			const outer& theOutter,
			const inner& theInner = nullptr
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
			, theOutter_(theOutter)
			, theInner_(theInner)
		{}

		Solid_Plane
		(
			const outer& theOutter,
			const inner& theInner = nullptr
		)
			: theOutter_(theOutter)
			, theInner_(theInner)
		{}

		Standard_Boolean HasHole() const
		{
			return (Standard_Boolean)theInner_;
		}

		Standard_Integer NbHoles() const
		{
			if (!HasHole()) return 0;
			return (Standard_Integer)theInner_->size();
		}

		const inner& Inner() const
		{
			return theInner_;
		}

		const outer& Outter() const
		{
			return theOutter_;
		}

		std::shared_ptr<Solid_Plane> This()
		{
			return shared_from_this();
		}

		std::shared_ptr<const Solid_Plane> This() const
		{
			return shared_from_this();
		}

		void RetrieveWiresTo(wireList& theWires) const;


		static std::shared_ptr<Solid_Plane> 
			MakePlane(const Solid_Face& theFace);
	};
}

#endif // !_Solid_Plane_Header
