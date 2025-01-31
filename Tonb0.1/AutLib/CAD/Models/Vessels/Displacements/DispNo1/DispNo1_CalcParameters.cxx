#include <Vessels_DispNo1.hxx>

#include <Pnt2d.hxx>
#include <DispNo1_Dim.hxx>
#include <Model_Dim.hxx>

#include <Geom2d_Line.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>

#define Interpd1(X, Val0, Val1)  \
   (Val1 - Val0)*X + Val0;

#define SmoothingParameter(XLIST, nbSections, WEIGHT, LEVEL)  \
   forThose(Index, 1, LEVEL) {Smoothing(XLIST, WEIGHT, nbSections);}

namespace AutLib
{

	static void Smoothing
	(
		realList& Parameters,
		const Standard_Real Coeff,
		const Standard_Integer nbSections
	)
	{
		forThose
		(
			Section,
			1,
			nbSections - 2
		)
		{
			Standard_Real Mean = MEAN
			(
				Parameters[Section - 1],
				Parameters[Section + 1]
			);

			Parameters[Section] += (Mean - Parameters[Section])*Coeff;
		}
	}
}

void AutLib::DispNo1_HullPatch::CalcxXSections()
{
	const DispNo1_Dimensions& dimensions = *this;

	Standard_Integer
		nbSections,
		Section;

	Standard_Real
		dx,
		AftCoeff,
		FwdCoeff,
		dxA,
		dxF;

	AftCoeff = dimension::SMALL_TOL;
	FwdCoeff = dimension::SMALL_TOL;

	nbSections = dimensions.NbNetColumns().Value();

	//Exclusion stem pair
	nbSections--;
	
	dx = dimensions.LengthOnDeck().Value() / (Standard_Real)(nbSections - 1);

	nbSections++;

	Section = 0;
	xXCoords[Section] = 0;

	Section = nbSections - 1;
	xXCoords[Section] = MIN(nbSections*dx, dimensions.LengthOnDeck().Value());

	Section = nbSections - 2;
	xXCoords[Section] = MIN(nbSections*dx, dimensions.LengthOnDeck().Value());

	dxA = ((Standard_Real)1.0 - AftCoeff)*dx;
	dxF = ((Standard_Real)1.0 - FwdCoeff)*dx;

	Standard_Real
		x0,
		x1;

	x0 = dxA;
	x1 = dimensions.LengthOnDeck().Value() - dxF;

	dx = (x1 - x0) / (Standard_Real)(nbSections - 4);

	forThose
	(
		Index,
		0,
		nbSections - 4
	)
	{
		Section = Index + 1;
		xXCoords[Section] = Index * dx + x0;
	}
}

void AutLib::DispNo1_HullPatch::CalcxYSections()
{
	const DispNo1_Dimensions& dimensions = *this;

	if (Deck.IsNull())
	{
		FatalErrorIn(FunctionSIG)
			<< " No Deck Profile has been found"
			<< abort(FatalError);
	}

	Standard_Integer nbSections = dimensions.NbNetColumns().Value();

	Pnt2d Point;
	Geom2dAPI_InterCurveCurve Intersection;
	Standard_Integer K = 0;
	for (const auto& X : xXCoords)
	{
		if (K == 0)
		{
			Point = Deck->Value(Deck->FirstParameter());
			xYCoords[K++] = Point.Y();
			continue;
		}

		if (K == xXCoords.size() - 1)
		{
			Point = Deck->Value(Deck->LastParameter());
			xYCoords[K++] = Point.Y();
			continue;
		}

		Handle(Geom2d_Line) Line = new Geom2d_Line(gp_Pnt2d(X, 0), gp_Dir2d(0, 1));

		Intersection.Init(Deck, Line, 1.0e-6);

		if (NOT Intersection.NbPoints())
		{
			FatalErrorIn(FunctionSIG)
				<< " No Intersection has been found"
				<< abort(FatalError);
		}

		if (Intersection.NbPoints() != 1)
		{
			Pnt2d sum(0, 0);
			forThose(I, 1, Intersection.NbPoints())
				sum += Intersection.Point(I);
			Point = sum / (Standard_Real)Intersection.NbPoints();
			/*FatalErrorIn(FunctionSIG)
				<< " More than one intersection point has been found"
				<< abort(FatalError);*/
		}
		else
		{
			Point = Intersection.Point(1);
		}

		xYCoords[K++] = Point.Y();
	}
}

void AutLib::DispNo1_HullPatch::CalcxZSections()
{
	const DispNo1_Dimensions & dimensions = *this;
	const DispNo1_KeelParams & keel = *this;

	Standard_Integer nbSections = dimensions.NbNetColumns().Value();

	Standard_Real Length = xXCoords[nbSections - 3];

	Standard_Real
		XRise,
		XPos,
		XVel0,
		XVel1;

	XRise = keel.RisePoint().Value()*Length;
	XPos = keel.Position().Value()*Length;
	XVel0 = keel.TransomSlope().Value()*XPos;
	XVel1 = XRise + keel.RiseSlope().Value()*(XPos - XRise);

	Standard_Real
		Parameter,
		xSection;

	forThose
	(
		Section,
		0,
		nbSections - 1
	)
	{
		xSection = xXCoords[Section];

		if (xSection <= XVel0)
		{
			xZCoords[Section] = dimensions.TransomHeight().Value();
		}
		else if (xSection >= XVel1)
		{
			xZCoords[Section] = (Standard_Real)0.;
		}
		else
		{
			Parameter = (xSection - XVel1) / (XVel0 - XVel1);

			Standard_Real Value = Interpd1
			(
				Parameter,
				(Standard_Real)0.,
				dimensions.TransomHeight().Value()
			);

			xZCoords[Section] = Value;
		}
	}

	if (ApplySmoothing())
	{
		SmoothingParameter
		(
			xZCoords,
			nbSections,
			DispNo1::SMOOTHING_WEIGHT,
			DispNo1::LEVEL_OF_SMOOTHING
		);
	}
}

void AutLib::DispNo1_HullPatch::CalcxDepthSections()
{
	const DispNo1_Dimensions & dimensions = *this;

	Standard_Real Length = dimensions.LengthOnDeck().Value();
	Standard_Real DepthAtBow = dimensions.DepthAtBow().Value();
	Standard_Real DepthAtTransom = dimensions.DepthAtTransom().Value();

	forThose
	(
		Section,
		0,
		dimensions.NbNetColumns().Value() - 1
	)
	{
		Standard_Real Parameter = xXCoords[Section] / Length;

		Standard_Real Value = Interpd1
		(
			Parameter,
			DepthAtTransom,
			DepthAtBow
		);

		xDepth[Section] = Value;
	}
}

void AutLib::DispNo1_HullPatch::CalcxDeadRise()
{
	const DispNo1_Dimensions & dimensions = *this;
	const DispNo1_HullParams& Hull = *this;

	Standard_Integer nbSections = dimensions.NbNetColumns().Value();

	Standard_Real Length = xXCoords[nbSections - 3];

	forThose
	(
		Section,
		0,
		nbSections - 3
	)
	{
		Standard_Real X = xXCoords[Section] / Length;

		if (X < (Standard_Real)0.5)
		{
			Standard_Real Value = Interpd1
			(
				(Standard_Real)2.0*X,
				Hull.AftSection().DeadRise().Value(),
				Hull.MidSection().DeadRise().Value()
			);

			xDeadRise[Section] = Value;
		}
		else
		{
			Standard_Real Value = Interpd1
			(
				(Standard_Real)2.0 * (X - (Standard_Real)0.5),
				Hull.MidSection().DeadRise().Value(),
				Hull.FwdSection().DeadRise().Value()
			);

			xDeadRise[Section] = Value;
		}
	}

	if (ApplySmoothing())
	{
		SmoothingParameter
		(
			xDeadRise,
			nbSections - 2,
			DispNo1::SMOOTHING_WEIGHT,
			DispNo1::LEVEL_OF_SMOOTHING
		);
	}
}

void AutLib::DispNo1_HullPatch::CalcxFlare()
{
	const DispNo1_Dimensions & dimensions = *this;
	const DispNo1_HullParams & Hull = *this;

	Standard_Integer nbSections = dimensions.NbNetColumns().Value();

	Standard_Real Length = dimensions.LengthOnDeck().Value();

	forThose
	(
		Section,
		0,
		nbSections - 1
	)
	{
		Standard_Real X = xXCoords[Section] / Length;

		if (X < (Standard_Real)0.5)
		{
			Standard_Real Value = Interpd1
			(
				(Standard_Real)2.0*X,
				Hull.AftSection().Flare().Value(),
				Hull.MidSection().Flare().Value()
			);

			xFlare[Section] = Value;
		}
		else
		{
			Standard_Real Value = Interpd1
			(
				(Standard_Real)2.0 * (X - (Standard_Real)0.5),
				Hull.MidSection().Flare().Value(),
				Hull.FwdSection().Flare().Value()
			);

			xFlare[Section] = Value;
		}
	}

	if (ApplySmoothing())
	{
		SmoothingParameter
		(
			xFlare,
			nbSections - 1,
			DispNo1::SMOOTHING_WEIGHT,
			DispNo1::LEVEL_OF_SMOOTHING
		);
	}
}

void AutLib::DispNo1_HullPatch::CalcxSideSlope()
{
	const DispNo1_Dimensions & dimensions = *this;
	const DispNo1_HullParams & Hull = *this;

	Standard_Integer nbSections = dimensions.NbNetColumns().Value();

	Standard_Real Length = dimensions.LengthOnDeck().Value();

	forThose
	(
		Section,
		0,
		nbSections - 1
	)
	{
		Standard_Real X = xXCoords[Section] / Length;

		if (X < (Standard_Real)0.5)
		{
			Standard_Real Value = Interpd1
			(
				(Standard_Real)2.0*X,
				Hull.AftSection().SideSlope().Value(),
				Hull.MidSection().SideSlope().Value()
			);

			xSideSlope[Section] = Value;
		}
		else
		{
			Standard_Real Value = Interpd1
			(
				(Standard_Real)2.0 * (X - (Standard_Real)0.5),
				Hull.MidSection().SideSlope().Value(),
				Hull.FwdSection().SideSlope().Value()
			);

			xSideSlope[Section] = Value;
		}
	}

	if (ApplySmoothing())
	{
		SmoothingParameter
		(
			xSideSlope,
			nbSections - 1,
			DispNo1::SMOOTHING_WEIGHT,
			DispNo1::LEVEL_OF_SMOOTHING
		);
	}
}

void AutLib::DispNo1_HullPatch::CalcxTightness()
{
	const DispNo1_Dimensions & dimensions = *this;
	const DispNo1_HullParams & Hull = *this;

	Standard_Integer nbSections = dimensions.NbNetColumns().Value();

	Standard_Real Length = xXCoords[nbSections - 3];

	forThose
	(
		Section,
		0,
		nbSections - 3
	)
	{
		Standard_Real X = xXCoords[Section] / Length;

		if (X < (Standard_Real)0.5)
		{
			Standard_Real Value = Interpd1
			(
				(Standard_Real)2.0*X,
				Hull.AftSection().Tightness().Value(),
				Hull.MidSection().Tightness().Value()
			);

			xTightness[Section] = Value;
		}
		else
		{
			Standard_Real Value = Interpd1
			(
				(Standard_Real)2.0 * (X - (Standard_Real)0.5),
				Hull.MidSection().Tightness().Value(),
				Hull.FwdSection().Tightness().Value()
			);

			xTightness[Section] = Value;
		}
	}

	if (ApplySmoothing())
	{
		SmoothingParameter
		(
			xTightness,
			nbSections - 2,
			DispNo1::SMOOTHING_WEIGHT,
			DispNo1::LEVEL_OF_SMOOTHING
		);
	}
}

void AutLib::DispNo1_HullPatch::CalcxRake()
{
	const DispNo1_Dimensions & dimensions = *this;
	const DispNo1_TransomParams& transom = *this;
	const DispNo1_StemParams& stem = *this;

	Standard_Integer nbSections = dimensions.NbNetColumns().Value();

	Standard_Real
		Length,
		xSection;

	Length = dimensions.LengthOnDeck().Value();

	forThose
	(
		Section,
		0,
		nbSections - 1
	)
	{
		xSection = xXCoords[Section] / Length;

		Standard_Real Value = Interpd1
		(
			xSection,
			transom.Rake().Value(),
			stem.StemRake().Value()
		);

		xRake[Section] = Value;
	}
}

void AutLib::DispNo1_HullPatch::CalcxParameters()
{
	CreateDeckProfile();

	CalcxYSections();

	CalcxZSections();

	CalcxDepthSections();

	CalcxDeadRise();

	CalcxSideSlope();

	CalcxTightness();

	CalcxFlare();

	CalcxRake();
}