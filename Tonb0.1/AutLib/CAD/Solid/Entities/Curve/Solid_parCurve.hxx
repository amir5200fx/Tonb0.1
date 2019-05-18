#pragma once
#ifndef _Solid_parCurve_Header
#define _Solid_parCurve_Header

#include <Standard_Handle.hxx>
#include <Standard_TypeDef.hxx>
#include <Global_Indexed.hxx>
#include <Precision.hxx>
#include <Pnt2d.hxx>

#include <memory>
#include <vector>

class Geom2d_Curve;

namespace AutLib
{

	// Forward Declarations
	template<class T> class Entity_Box;
	template<class T> class Entity_Polygon;

	typedef Entity_Box<Pnt2d> Entity2d_Box;
	typedef Entity_Polygon<Pnt2d> Entity2d_Polygon;

	struct Solid_parCurveInfo
	{

		static Standard_Integer NB_OF_DIVISION;
	};

	class Solid_parCurve
		: public Solid_parCurveInfo
		, public Global_Indexed
	{

		typedef std::shared_ptr<Solid_parCurve> pCurve_ptr;
		typedef std::vector<Pnt2d> ptList;
		typedef std::vector<Standard_Real> realList;
		typedef std::vector<pCurve_ptr> curveList;

		/*Private Data*/

		Handle(Geom2d_Curve) theCurve_;

		Standard_Real theFirst_;
		Standard_Real theLast_;

		Standard_Boolean theSense_;

		void CheckCurve() const;

	public:

		Solid_parCurve
		(
			const Standard_Real theFirst, 
			const Standard_Real theLast,
			const Handle(Geom2d_Curve)& theCurve,
			const Standard_Boolean Reversed = Standard_False
		)
			: theFirst_(theFirst)
			, theLast_(theLast)
			, theCurve_(theCurve)
			, theSense_(Reversed)
		{
			CheckCurve();
		}

		Standard_Boolean Reversed() const
		{
			return theSense_;
		}

		const Handle(Geom2d_Curve)& Curve() const
		{
			return theCurve_;
		}

		Standard_Real FirstParameter() const
		{
			return theFirst_;
		}

		Standard_Real LastParameter() const
		{
			return theLast_;
		}

		Standard_Boolean IsClosed(const Standard_Real theTol = Precision::Confusion()) const;

		Pnt2d Start() const;

		Pnt2d Last() const;

		Pnt2d Value(const Standard_Real x) const;

		Pnt2d NormalizedParameterValue(const Standard_Real x) const;

		Entity2d_Box BoundingBox(const Standard_Real theTol = 0.0) const;

		std::shared_ptr<Entity2d_Polygon> UniformParametricDiscretized(const Standard_Integer nbSegments) const;

		void ReverseGeometry();

		void Split(const Standard_Real x, pCurve_ptr& theC1, pCurve_ptr& theC2) const;

		void ExportToPlt(OFstream& File) const;

		void ExportTopologyToPlt(OFstream& File) const;

		/*void Split(const Standard_Real x, Pnt2d& theP, pCurve_ptr& theC1, pCurve_ptr& theC2) const;

		template<bool Sorted = true>
		void Split(const realList& theParams, ptList& thePts, curveList& theCurves, const Standard_Real theTol = Precision::Confusion()) const;

		template<>
		void Split<false>(const realList& theParams, ptList& thePts, curveList& theCurves, const Standard_Real theTol) const;

		void Mirror(const gp_Pnt2d& P);

		void Mirror(const gp_Ax2d& A);

		void Rotate(const gp_Pnt2d& P, const Standard_Real Ang);

		void Scale(const gp_Pnt2d& P, const Standard_Real S);

		void Translate(const gp_Vec2d& V);

		void Translate(const gp_Pnt2d& P1, const gp_Pnt2d& P2);

		void Transform(const gp_Trsf2d& T);*/

	};
}

#endif // !_Solid_parCurve_Header
