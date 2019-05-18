#include <Solid_parCurve.hxx>

#include <Entity2d_Box.hxx>
#include <Entity2d_Polygon.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>
#include <Bnd_Box2d.hxx>
#include <BndLib_Add2dCurve.hxx>

using namespace AutLib;

namespace AutLib
{
	Standard_Integer Solid_parCurve::NB_OF_DIVISION(40);
}

void AutLib::Solid_parCurve::CheckCurve() const
{
	if (theCurve_.IsNull())
	{
		FatalErrorIn("void AutLib::Solid_parCurve::CheckCurve()")
			<< "Null pointer encountered!" << endl
			<< abort(FatalError);
	}

	if (LastParameter() <= FirstParameter())
	{
		FatalErrorIn("void AutLib::Solid_parCurve::CheckCurve()")
			<< "Invalid Parameters :" << endl
			<< " - Start parameter: " << FirstParameter() << endl
			<< " - Last parameter: " << LastParameter() << endl
			<< abort(FatalError);
	}
}

Standard_Boolean AutLib::Solid_parCurve::IsClosed(const Standard_Real theTol) const
{
	return SquareDistance(Start(), Last()) <= theTol * theTol;
}

Pnt2d AutLib::Solid_parCurve::Start() const
{
	Debug_Null_Pointer(theCurve_);

	return theCurve_->Value(FirstParameter());
}

Pnt2d AutLib::Solid_parCurve::Last() const
{
	Debug_Null_Pointer(theCurve_);

	return theCurve_->Value(LastParameter());
}

Pnt2d AutLib::Solid_parCurve::Value(const Standard_Real x) const
{
	if (NOT INSIDE(x, FirstParameter(), LastParameter()))
	{
		FatalErrorIn("Pnt2d AutLib::Solid_parCurve::Value(const Standard_Real x) const")
			<< "Invalid Parameter: " << x << endl
			<< " - First Parameter: " << FirstParameter() << endl
			<< " - Last Parameter: " << LastParameter() << endl
			<< abort(FatalError);
	}
	return theCurve_->Value(x);
}

Pnt2d AutLib::Solid_parCurve::NormalizedParameterValue(const Standard_Real x) const
{
	if (NOT INSIDE(x, 0, 1))
	{
		FatalErrorIn("Pnt2d AutLib::Solid_parCurve::Value(const Standard_Real x) const")
			<< "Invalid Parameter: " << x << endl
			<< " - First Parameter: " << 0 << endl
			<< " - Last Parameter: " << 1 << endl
			<< abort(FatalError);
	}
	return theCurve_->Value(FirstParameter() + x * (LastParameter() - FirstParameter()));
}

Entity2d_Box AutLib::Solid_parCurve::BoundingBox(const Standard_Real theTol) const
{
	Debug_Null_Pointer(theCurve_);
	Bnd_Box2d BndBox;
	BndLib_Add2dCurve::Add(theCurve_, theFirst_, theLast_, theTol, BndBox);

	Standard_Real Xmin, Xmax, Ymin, Ymax;
	BndBox.Get(Xmin, Ymin, Xmax, Ymax);

	Entity2d_Box box(Pnt2d(Xmin, Ymin), Pnt2d(Xmax, Ymax));
	return std::move(box);
}

std::shared_ptr<Entity2d_Polygon>
AutLib::Solid_parCurve::UniformParametricDiscretized
(
	const Standard_Integer nbSegments
) const
{
	if (nbSegments < 1)
	{
		FatalErrorIn("std::shared_ptr<Solid_parCurve> UniformParametricDiscretized(const Standard_Integer nbSegments) const")
			<< "Invalid nb. of segments: " << nbSegments << endl
			<< abort(FatalError);
	}

	std::shared_ptr<Entity2d_Polygon> polygon = std::make_shared<Entity2d_Polygon>();
	auto& points = polygon->Points();

	points.reserve(nbSegments + 1);

	auto du = (LastParameter() - FirstParameter()) / (Standard_Real)nbSegments;
	auto u0 = FirstParameter();

	points.push_back(Start());
	for (int k = 1; k < nbSegments; k++)
	{
		auto p = (Standard_Real)k*du + u0;
		points.push_back(Value(p));
	}
	points.push_back(Last());
	return std::move(polygon);
}

void AutLib::Solid_parCurve::ReverseGeometry()
{
	Debug_Null_Pointer(theCurve_);
	theCurve_->Reverse();

	auto temp = theLast_;
	theLast_ = theCurve_->ReversedParameter(theFirst_);
	theFirst_ = theCurve_->ReversedParameter(temp);
}

void AutLib::Solid_parCurve::Split
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

	theC1 = std::make_shared<Solid_parCurve>(theFirst_, x, theCurve_, theSense_);
	theC2 = std::make_shared<Solid_parCurve>(x, theLast_, theCurve_, theSense_);
}