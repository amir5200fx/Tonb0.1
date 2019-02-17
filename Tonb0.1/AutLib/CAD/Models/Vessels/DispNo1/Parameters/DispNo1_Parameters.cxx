#include <DispNo1_Parameters.hxx>

#include <DispNo1_DefaultParams.hxx>

AutLib::DispNo1::Dimensions::Dimensions()
	: theDraft_(DRAFT)
	, theTransomHeight_(TRANSOM_HEIGHT)
	, theDepthAtBow_(DEPTH_AT_BOW)
	, theDepthAtTransom_(DEPTH_AT_TRANSOM)
	, theBeamOnDeck_(BEAM_ON_DECK)
	, theLengthOnDeck_(LENGTH_ON_DECK)
	, theNbNetRows_(NB_OF_NET_ROWS)
	, theNbNetColumns_(NB_OF_NET_COLUMNS)
{}

AutLib::DispNo1::AftSectionParams::AftSectionParams()
	: SectionParamsBase
	(
		AFT_TIGHTNESS,
		AFT_DEADRISE,
		AFT_SIDE_SLOPE,
		AFT_FLARE
	)
{}

AutLib::DispNo1::MidSectionParams::MidSectionParams()
	: SectionParamsBase
	(
		MID_TIGHTNESS,
		MID_DEADRISE,
		MID_SIDE_SLOPE,
		MID_FLARE
	)
{}

AutLib::DispNo1::FwdSectionParams::FwdSectionParams()
	: SectionParamsBase
	(
		FWD_TIGHTNESS,
		FWD_DEADRISE,
		FWD_SIDE_SLOPE,
		FWD_FLARE
	)
{}

AutLib::DispNo1::KeelParams::KeelParams()
	: thePosition_(KEEL_POSITION)
	, theRisePoint_(KEEL_RISE_POINT)
	, theRiseSlope_(KEEL_RISE_SLOPE)
	, theTransomSlope_(KELL_TRANSOM_SLOPE)
{}

AutLib::DispNo1::StemParams::StemParams()
	: theBowRounding_(BOW_ROUNDING)
	, theStemRake_(STEM_RAKE)
	, theForeFootShape_(FORE_FOOT_SHAPE)
{}

AutLib::DispNo1::TransomParams::TransomParams()
	: theRake_(TRANSOM_RAKE)
	, theWidth_(TRANSOM_WIDTH)
{}

AutLib::DispNo1::HullParams::HullParams()
	: theMaxAreaLocation_(MAX_AREA_LOCATION)
	, theFwdFullness_(FWD_FULLNESS)
	, theAftFullness_(AFT_FULLNESS)
{}