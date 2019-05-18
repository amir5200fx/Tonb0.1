#pragma once
#ifndef _Solid_Curve_Header
#define _Solid_Curve_Header

#include <Standard_Handle.hxx>
#include <Standard_TypeDef.hxx>
#include <Precision.hxx>
#include <Pnt3d.hxx>
#include <OFstream.hxx>

class Geom_Curve;

namespace AutLib
{

	template<class T>
	class Entity_Box;

	typedef Entity_Box<Pnt3d> Entity3d_Box;

	struct Solid_CurveInfo
	{

		static Standard_Integer NB_OF_DIVISION;
	};

	class Solid_Curve
		: public Solid_CurveInfo
	{

		typedef std::shared_ptr<Solid_Curve> pCurve_ptr;

		/*Private Data*/

		Handle(Geom_Curve) theCurve_;

		Standard_Real theFirst_;
		Standard_Real theLast_;

		Standard_Boolean theSense_;

		void CheckCurve() const;

	public:

		Solid_Curve
		(
			const Standard_Real theFirst,
			const Standard_Real theLast,
			const Handle(Geom_Curve)& theCurve,
			const Standard_Boolean theSense = Standard_True
		)
			: theFirst_(theFirst)
			, theLast_(theLast)
			, theCurve_(theCurve)
			, theSense_(theSense)
		{
			//CheckCurve();
		}

		const Handle(Geom_Curve)& Curve() const
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

		Standard_Boolean IsDegenerated(const Standard_Real theTol = Precision::PConfusion()) const
		{
			return ABS(FirstParameter() - LastParameter()) <= theTol;
		}

		Standard_Real IsValid() const
		{
			return FirstParameter() <= LastParameter();
		}

		Pnt3d Start() const;

		Pnt3d Last() const;

		Pnt3d Value(const Standard_Real x) const;

		Pnt3d NormalizedParameterValue(const Standard_Real x) const;

		Entity3d_Box BoundingBox(const Standard_Real theTol = 0.0) const;

		void Split
		(
			const Standard_Real x,
			pCurve_ptr& theC1,
			pCurve_ptr& theC2
		) const;

		void ReverseGeometry();

		void ExportToPlt(OFstream& File) const;

		void ExportTopologyToPlt(OFstream& File) const;
	};
}

#endif // !_Solid_Curve_Header
