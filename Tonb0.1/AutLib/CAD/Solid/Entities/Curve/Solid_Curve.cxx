#include <Solid_Curve.hxx>

#include <Entity3d_Box.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <Bnd_Box.hxx>
#include <BndLib_Add3dCurve.hxx>
#include <GeomAdaptor_Curve.hxx>
#include <Geom_Curve.hxx>

using namespace AutLib;

namespace AutLib
{
	Standard_Integer Solid_CurveInfo::NB_OF_DIVISION(40);
}

void AutLib::Solid_Curve::CheckCurve() const
{
	if (theCurve_.IsNull())
	{
		FatalErrorIn("void AutLib::Solid_Curve::CheckCurve()")
			<< "Null pointer encountered!" << endl
			<< abort(FatalError);
	}

	if (!IsValid())
	{
		FatalErrorIn("void AutLib::Solid_Curve::CheckCurve()")
			<< "Invalid Parameters :" << endl
			<< " - Start parameter: " << FirstParameter() << endl
			<< " - Last parameter: " << LastParameter() << endl
			<< abort(FatalError);
	}
}

Standard_Boolean AutLib::Solid_Curve::IsClosed(const Standard_Real theTol) const
{
	return SquareDistance(Start(), Last()) <= theTol * theTol;
}

Pnt3d AutLib::Solid_Curve::Start() const
{
	Debug_Null_Pointer(theCurve_);

	return theCurve_->Value(FirstParameter());
}

Pnt3d AutLib::Solid_Curve::Last() const
{
	Debug_Null_Pointer(theCurve_);

	return theCurve_->Value(LastParameter());
}

Pnt3d AutLib::Solid_Curve::Value(const Standard_Real x) const
{
	if (NOT INSIDE(x, FirstParameter(), LastParameter()))
	{
		FatalErrorIn("Pnt3d AutLib::Solid_Curve::Value(const Standard_Real x) const")
			<< "Invalid Parameter: " << x << endl
			<< " - First Parameter: " << FirstParameter() << endl
			<< " - Last Parameter: " << LastParameter() << endl
			<< abort(FatalError);
	}
	return theCurve_->Value(x);
}

Pnt3d AutLib::Solid_Curve::NormalizedParameterValue(const Standard_Real x) const
{
	if (NOT INSIDE(x, 0, 1))
	{
		FatalErrorIn("Pnt3d AutLib::Solid_Curve::Value(const Standard_Real x) const")
			<< "Invalid Parameter: " << x << endl
			<< " - First Parameter: " << 0 << endl
			<< " - Last Parameter: " << 1 << endl
			<< abort(FatalError);
	}
	return theCurve_->Value(FirstParameter() + x * (LastParameter() - FirstParameter()));
}

Entity3d_Box AutLib::Solid_Curve::BoundingBox(const Standard_Real theTol) const
{
	Bnd_Box BndBox;
	BndLib_Add3dCurve::Add
	(
		GeomAdaptor_Curve(theCurve_),
		theFirst_,
		theLast_,
		theTol,
		BndBox
	);

	Standard_Real Xmin, Xmax, Ymin, Ymax, Zmin, Zmax;
	BndBox.Get(Xmin, Ymin, Zmin, Xmax, Ymax, Zmax);

	Entity3d_Box box(Pnt3d(Xmin, Ymin, Zmin), Pnt3d(Xmax, Ymax, Zmax));
	return std::move(box);
}

void AutLib::Solid_Curve::Split
(
	const Standard_Real x,
	pCurve_ptr & theC1,
	pCurve_ptr & theC2
) const
{
	if (NOT INSIDE(x, theFirst_, theLast_))
	{
		FatalErrorIn("void Split(const Standard_Real x, pCurve_ptr& theC1, pCurve_ptr& theC2, const Standard_Real theTol) const")
			<< "The Parameter is out of valid range: " << x << endl
			<< " - First parameter: " << theFirst_ << endl
			<< " - Last Parameter: " << theLast_ << endl
			<< abort(FatalError);
	}

	theC1 = std::make_shared<Solid_Curve>(theFirst_, x, theCurve_, theSense_);
	theC2 = std::make_shared<Solid_Curve>(x, theLast_, theCurve_, theSense_);
}

