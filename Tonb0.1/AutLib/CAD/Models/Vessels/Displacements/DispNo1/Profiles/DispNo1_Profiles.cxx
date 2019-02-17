#include <Vessels_DispNo1.hxx>

#include <DispNo1_Dim.hxx>

#include <Pnt2d.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColgp_Array1OfPnt2d.hxx>

void AutLib::DispNo1_HullPatch::CreateDeckProfile()
{
	const DispNo1_Dimensions& dimensions = *this;
	const DispNo1_HullParams& hull = *this;
	const DispNo1_TransomParams& transom = *this;
	const DispNo1_StemParams& stem = *this;

	DispNo1_Profile& profile = *this;

	Standard_Integer nbPoles = 7;
	TColgp_Array1OfPnt2d Points(1, nbPoles);

	Pnt2d P1 = Pnt2d(0, transom.Width().Value()*dimensions.BeamOnDeck().Value());
	Pnt2d P2 = Pnt2d(0, dimensions.BeamOnDeck().Value());
	Pnt2d P4 = Pnt2d(hull.MaxAreaLocation().Value()*dimensions.LengthOnDeck().Value(), dimensions.BeamOnDeck().Value());
	Pnt2d P6 = Pnt2d(dimensions.LengthOnDeck().Value(), dimensions.BeamOnDeck().Value());
	Pnt2d P7 = Pnt2d(dimensions.LengthOnDeck().Value(), stem.BowRounding().Value()*dimensions.BeamOnDeck().Value());

	Pnt2d P3 = P4 + (P2 - P4)*hull.AftFullness().Value();
	Pnt2d P5 = P4 + 0.95*(P6 - P4)*hull.FwdFullness().Value();

	Points.SetValue(1, P1);
	Points.SetValue(2, P2);
	Points.SetValue(3, P3);
	Points.SetValue(4, P4);
	Points.SetValue(5, P5);
	Points.SetValue(6, P6);
	Points.SetValue(7, P7);

	TColStd_Array1OfReal Weights(1, nbPoles);
	Weights.Init(1);

	Standard_Integer
		MaxIndex,
		Degree;

	MaxIndex = nbPoles - 1;
	Degree = 2;

	TColStd_Array1OfReal Knots(1, 4);
	TColStd_Array1OfInteger Mults(1, 4);

	Knots.SetValue(1, 0);
	Knots.SetValue(2, 0.25);
	Knots.SetValue(3, 0.75);
	Knots.SetValue(4, 1);

	Mults.SetValue(1, 3);
	Mults.SetValue(2, 2);
	Mults.SetValue(3, 2);
	Mults.SetValue(4, 3);

	profile.Deck =
		new Geom2d_BSplineCurve(Points, Weights, Knots, Mults, Degree);
}

void AutLib::DispNo1_HullPatch::CreateFlareProfile
(
	const Standard_Integer theSection
)
{
	const DispNo1_Dimensions& dimensions = *this;

	DispNo1_Profile& profile = *this;
	DispNo1_Xparams& xParams = *this;
	auto& Section = *xParams.xSection[theSection];

	Standard_Integer nbPoints = (Standard_Integer)Section.CtrlPts.size();
	Standard_Integer corner = Section.Corner;

	auto& CtrlPoints = Section.CtrlPts;

	Standard_Integer NbPoles = 3;
	TColgp_Array1OfPnt2d Poles(1, NbPoles);

	Poles.SetValue(1, gp_Pnt2d(CtrlPoints[corner].Y(), CtrlPoints[corner].Z()));
	Poles.SetValue(3, gp_Pnt2d(CtrlPoints[nbPoints - 1].Y(), CtrlPoints[nbPoints - 1].Z()));

	Poles.SetValue(2, gp_Pnt2d(Poles.Value(1).X(), Poles.Value(3).Y()));

	TColStd_Array1OfReal Weights(1, NbPoles);
	Weights.Init(1);
	Weights.SetValue(2, MAX(xParams.xFlare[theSection], DispNo1::MIN_FLARE));

	Standard_Integer
		MaxIndex,
		Degree;

	MaxIndex = NbPoles - 1;
	Degree = 2;

	TColStd_Array1OfReal Knots(1, 2);
	Knots.SetValue(1, 0);
	Knots.SetValue(2, 1);

	TColStd_Array1OfInteger Mults(1, 2);
	Mults.SetValue(1, 3);
	Mults.SetValue(2, 3);

	profile.Flares[theSection] =
		new Geom2d_BSplineCurve(Poles, Weights, Knots, Mults, Degree);
}

void AutLib::DispNo1_HullPatch::CreateFlareProfile()
{
	const DispNo1_Dimensions& dimensions = *this;

	for (int section = 0; section < dimensions.NbNetColumns().Value(); section++)
	{
		CreateFlareProfile
		(
			section
		);
	}
}