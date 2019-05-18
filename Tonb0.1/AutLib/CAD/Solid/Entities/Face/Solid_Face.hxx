#pragma once
#ifndef _Solid_Face_Header
#define _Solid_Face_Header

#include <Pnt3d.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Solid_Entity.hxx>
#include <OFstream.hxx>

#include <Standard_Handle.hxx>
#include <TopoDS_Face.hxx>

#include <vector>
#include <memory>

class Geom_Surface;
class Poly_Triangulation;

namespace AutLib
{

	enum Face_Orientation
	{
		Face_Orientation_UNKNOWN = 0,
		Face_Orientation_INWARD,
		Face_Orientation_OUTWARD
	};

	// Forward Declarations
	class Solid_Edge;
	class Solid_Wire;

	template<class T> class Entity_Box;

	typedef Entity_Box<Pnt3d> Entity3d_Box;

	class Solid_Face_parametricBounds
	{

		/*Private Data*/

		Standard_Real theUmin_;
		Standard_Real theUmax_;
		Standard_Real theVmin_;
		Standard_Real theVmax_;

	protected:

		void SetParametricBounds
		(
			Standard_Real Umin,
			Standard_Real Umax,
			Standard_Real Vmin,
			Standard_Real Vmax
		)
		{
			theUmin_ = Umin;
			theUmax_ = Umax;
			theVmin_ = Vmin;
			theUmax_ = Vmax;
		}

	public:

		Solid_Face_parametricBounds()
		{}

		void GetParametricBouns
		(
			Standard_Real& Umin,
			Standard_Real& Umax,
			Standard_Real& Vmin,
			Standard_Real& Vmax
		) const
		{
			Umin = theUmin_;
			Umax = theUmax_;
			Vmin = theVmin_;
			Vmax = theVmax_;
		}

	};

	class Solid_Face
		: public Solid_Entity
		//, public Solid_Face_parametricBounds
		, public std::enable_shared_from_this<Solid_Face>
	{

		typedef std::shared_ptr<Solid_Edge> edge_ptr;
		typedef std::shared_ptr<Entity3d_Box> box_ptr;
		typedef std::shared_ptr<Solid_Wire> wire_ptr;

		typedef wire_ptr outer;
		typedef std::shared_ptr<std::vector<wire_ptr>> inner;

		typedef std::vector<edge_ptr> edgeList;
		typedef std::shared_ptr<edgeList> edgeList_ptr;

		/*Private Data*/

		Handle(Geom_Surface) theGeom_;
		Handle(Poly_Triangulation) theTriangulation_;

		outer theOuter_;
		inner theInner_;

		box_ptr theBoundingBox_;

		Face_Orientation theOrientation_;

		TopoDS_Face theTFace_;

	public:

		Solid_Face
		(
			const Handle(Geom_Surface)& theGeom,
			const outer& theOuter,
			const inner& theInner
		)
			: theGeom_(theGeom)
			, theOuter_(theOuter)
			, theInner_(theInner)
		{}

		Solid_Face
		(
			const Standard_Integer theIndex,
			const Handle(Geom_Surface)& theGeom,
			const outer& theOuter,
			const inner& theInner
		)
			: Solid_Entity(theIndex)
			, theGeom_(theGeom)
			, theOuter_(theOuter)
			, theInner_(theInner)
		{}

		Solid_Face
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom_Surface)& theGeom,
			const outer& theOuter,
			const inner& theInner
		)
			: Solid_Entity(theIndex, theName)
			, theGeom_(theGeom)
			, theOuter_(theOuter)
			, theInner_(theInner)
		{}

		const outer& OuterWire() const
		{
			return theOuter_;
		}

		const inner& InnerWires() const
		{
			return theInner_;
		}

		const Handle(Geom_Surface)& Geometry() const
		{
			return theGeom_;
		}

		const Handle(Poly_Triangulation)& Triangulation() const
		{
			return theTriangulation_;
		}

		edgeList Edges() const;

		const box_ptr& BoundingBox() const
		{
			return theBoundingBox_;
		}

		TopoDS_Face TFace() const
		{
			return theTFace_;
		}

		Face_Orientation Orientation() const
		{
			return theOrientation_;
		}

		Standard_Boolean IsClamped() const;

		Entity2d_Box CalcParametricBoundingBox() const;

		void SetOrientation(const Face_Orientation theOrientation)
		{
			theOrientation_ = theOrientation;
		}

		void SetTFace(const TopoDS_Face theFace)
		{
			theTFace_ = theFace;
		}

		void CalcBoundingBox();

		void ExportToPlt(fstream& File) const;

		void ExportToPlt(OFstream& File) const;

		static Standard_Boolean IsLess
		(
			const std::shared_ptr<Solid_Face>& theFace0,
			const std::shared_ptr<Solid_Face>& theFace1
		)
		{
			Debug_Null_Pointer(theFace0);
			Debug_Null_Pointer(theFace1);

			return theFace0->Index() < theFace1->Index();
		}

		static Standard_Boolean IsLess
		(
			const std::weak_ptr<Solid_Face>& theFace0,
			const std::weak_ptr<Solid_Face>& theFace1
		)
		{
			Debug_Null_Pointer(theFace0.lock());
			Debug_Null_Pointer(theFace1.lock());

			return theFace0.lock()->Index() < theFace1.lock()->Index();
		}
	};
}

#endif // !_Solid_Face_Header
