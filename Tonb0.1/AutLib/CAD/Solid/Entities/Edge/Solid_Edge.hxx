#pragma once
#ifndef _Solid_Edge_Header
#define _Solid_Edge_Header

#include <Cad_EntityPrecision.hxx>
#include <Solid_Entity.hxx>

#include <TopoDS_Edge.hxx>

#include <memory>

class TopoDS_Edge;

namespace AutLib
{

	// Forward Declarations
	class Solid_parCurve;
	class Solid_Curve;
	class Solid_Vertex;
	class Solid_Face;
	class Solid_Paired;
	class Solid_Wire;

	class Solid_Edge
		: public Solid_Entity
		, public Cad_EntityPrecision
		, public std::enable_shared_from_this<Solid_Edge>
	{

	public:

		typedef std::shared_ptr<Solid_Vertex> vertex_ptr;
		typedef std::shared_ptr<Solid_Curve> curve_ptr;
		typedef std::shared_ptr<Solid_parCurve> parCurve_ptr;

		typedef std::weak_ptr<Solid_Face> face_weak;
		typedef std::weak_ptr<Solid_Edge> edge_weak;
		typedef std::weak_ptr<Solid_Paired> paired_weak;
		typedef std::weak_ptr<Solid_Wire> wire_weak;

	private:

		/*Private Data*/

		vertex_ptr theStart_;
		vertex_ptr theEnd_;

		parCurve_ptr thePar_;

		curve_ptr theCurve_;

		face_weak theFace_;
		paired_weak thePaired_;
		edge_weak thePairedEdge_;
		wire_weak theWire_;

		Standard_Boolean theSense_;

		TopoDS_Edge theTEdge_;

		void CheckEdge();

	public:

		Solid_Edge
		(
			const Standard_Integer theIndex,
			const word& theName,
			const vertex_ptr& theVtx0,
			const vertex_ptr& theVtx1,
			const curve_ptr& theCurve,
			const Standard_Boolean theSense = Standard_True
		)
			: Solid_Entity(theIndex, theName)
			, theStart_(theVtx0)
			, theEnd_(theVtx1)
			, theCurve_(theCurve)
			, theSense_(theSense)
		{
			//CheckEdge();
		}

		Solid_Edge
		(
			const Standard_Integer theIndex,
			const vertex_ptr& theVtx0,
			const vertex_ptr& theVtx1,
			const curve_ptr& theCurve,
			const Standard_Boolean theSense = Standard_True
		)
			: Solid_Entity(theIndex)
			, theStart_(theVtx0)
			, theEnd_(theVtx1)
			, theCurve_(theCurve)
			, theSense_(theSense)
		{
			//CheckEdge();
		}

		Solid_Edge
		(
			const vertex_ptr& theVtx0,
			const vertex_ptr& theVtx1,
			const curve_ptr& theCurve,
			const Standard_Boolean theSense = Standard_True
		)
			: theStart_(theVtx0)
			, theEnd_(theVtx1)
			, theCurve_(theCurve)
			, theSense_(theSense)
		{
			//CheckEdge();
		}

		Solid_Edge
		(
			const Standard_Integer theIndex,
			const curve_ptr& theCurve,
			const Standard_Boolean theSense = Standard_True
		)
			: Solid_Entity(theIndex)
			, theCurve_(theCurve)
			, theSense_(theSense)
		{}

		Solid_Edge
		(
			const curve_ptr& theCurve,
			const Standard_Boolean theSense = Standard_True
		)
			: theCurve_(theCurve)
			, theSense_(theSense)
		{}

		virtual ~Solid_Edge()
		{}

		Standard_Boolean IsDegenerated() const;

		Standard_Boolean IsRing() const;

		Standard_Boolean Sense() const
		{
			return theSense_;
		}

		TopoDS_Edge TEdge() const
		{
			return theTEdge_;
		}

		const curve_ptr& Geometry() const
		{
			return theCurve_;
		}

		const vertex_ptr& Start() const
		{
			return theStart_;
		}

		vertex_ptr& Start()
		{
			return theStart_;
		}

		const vertex_ptr& End() const
		{
			return theEnd_;
		}

		vertex_ptr& End()
		{
			return theEnd_;
		}

		const parCurve_ptr& Par() const
		{
			return thePar_;
		}

		const face_weak& Face() const
		{
			return theFace_;
		}

		const paired_weak& Paired() const
		{
			return thePaired_;
		}

		const edge_weak& PairedEdge() const
		{
			return thePairedEdge_;
		}

		const wire_weak& Wire() const
		{
			return theWire_;
		}

		void SetFace(const face_weak& theFace)
		{
			theFace_ = theFace;
		}

		void SetPaired(const paired_weak& thePaired)
		{
			thePaired_ = thePaired;
		}

		void SetPairedEdge(const edge_weak& thePaired)
		{
			thePairedEdge_ = thePaired;
		}

		void SetPar(const parCurve_ptr& thePar)
		{
			thePar_ = thePar;
		}

		void SetWire(const wire_weak& theWire)
		{
			theWire_ = theWire;
		}

		void SetTEdge(const TopoDS_Edge& theEdge)
		{
			theTEdge_ = theEdge;
		}

		void Reverse()
		{
			std::swap(theStart_, theEnd_);
			theSense_ = !theSense_;
		}

		std::shared_ptr<Solid_Edge> This()
		{
			return shared_from_this();
		}

		std::shared_ptr<const Solid_Edge> This() const
		{
			return shared_from_this();
		}

		static Standard_Boolean IsLess
		(
			const std::weak_ptr<Solid_Edge>& theEdge1,
			const std::weak_ptr<Solid_Edge>& theEdge2
		)
		{
			const auto edge1 = theEdge1.lock();
			const auto edge2 = theEdge2.lock();

			Debug_Null_Pointer(edge1);
			Debug_Null_Pointer(edge2);

			return edge1->Index() < edge2->Index();
		}

		static Standard_Boolean IsLess
		(
			const std::shared_ptr<Solid_Edge>& edge1,
			const std::shared_ptr<Solid_Edge>& edge2
		)
		{
			Debug_Null_Pointer(edge1);
			Debug_Null_Pointer(edge2);

			return edge1->Index() < edge2->Index();
		}
	};
}

#endif // !_Solid_Edge_Header
