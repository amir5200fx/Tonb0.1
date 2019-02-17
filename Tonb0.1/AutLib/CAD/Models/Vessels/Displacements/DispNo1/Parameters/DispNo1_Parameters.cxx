#include <DispNo1_Parameters.hxx>

#include <DispNo1_DefaultParams.hxx>

using namespace AutLib;
using namespace DispNo1;

Standard_Boolean AutLib::DispNo1_ManipParams::IsManipulated(Standard_True);

AutLib::DispNo1_Dimensions::DispNo1_Dimensions()
	: theDraft_(DRAFT)
	, theTransomHeight_(TRANSOM_HEIGHT)
	, theDepthAtBow_(DEPTH_AT_BOW)
	, theDepthAtTransom_(DEPTH_AT_TRANSOM)
	, theBeamOnDeck_(BEAM_ON_DECK)
	, theLengthOnDeck_(LENGTH_ON_DECK)
	, theNbNetRows_(NB_OF_NET_ROWS)
	, theNbNetColumns_(NB_OF_NET_COLUMNS)
{}

AutLib::DispNo1_AftSectionParams::DispNo1_AftSectionParams()
	: DispNo1_SectionParamsBase
	(
		AFT_TIGHTNESS,
		AFT_DEADRISE,
		AFT_SIDE_SLOPE,
		AFT_FLARE
	)
{}

AutLib::DispNo1_MidSectionParams::DispNo1_MidSectionParams()
	: DispNo1_SectionParamsBase
	(
		MID_TIGHTNESS,
		MID_DEADRISE,
		MID_SIDE_SLOPE,
		MID_FLARE
	)
{}

AutLib::DispNo1_FwdSectionParams::DispNo1_FwdSectionParams()
	: DispNo1_SectionParamsBase
	(
		FWD_TIGHTNESS,
		FWD_DEADRISE,
		FWD_SIDE_SLOPE,
		FWD_FLARE
	)
{}

AutLib::DispNo1_KeelParams::DispNo1_KeelParams()
	: thePosition_(KEEL_POSITION)
	, theRisePoint_(KEEL_RISE_POINT)
	, theRiseSlope_(KEEL_RISE_SLOPE)
	, theTransomSlope_(KELL_TRANSOM_SLOPE)
{}

AutLib::DispNo1_StemParams::DispNo1_StemParams()
	: theBowRounding_(BOW_ROUNDING)
	, theStemRake_(STEM_RAKE)
	, theForeFootShape_(FORE_FOOT_SHAPE)
{}

AutLib::DispNo1_TransomParams::DispNo1_TransomParams()
	: theRake_(TRANSOM_RAKE)
	, theWidth_(TRANSOM_WIDTH)
{}

AutLib::DispNo1_HullParams::DispNo1_HullParams()
	: theMaxAreaLocation_(MAX_AREA_LOCATION)
	, theFwdFullness_(FWD_FULLNESS)
	, theAftFullness_(AFT_FULLNESS)
{}