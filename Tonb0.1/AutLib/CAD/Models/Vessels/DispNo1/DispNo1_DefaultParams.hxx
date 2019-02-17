#pragma once
#ifndef _DispNo1_DefaultParams_Header
#define _DispNo1_DefaultParams_Header

#include <Smart_Variable.hxx>

namespace AutLib
{

	namespace DispNo1
	{

		// Dimension Parameters
		/*--> Param. nb  1:*/ static const Variables::length LENGTH_ON_DECK("lengthOnDeck", (scalar)160., UnitSystem_Length_m);
		/*--> Param. nb  2:*/ static const Variables::length BEAM_ON_DECK("beamOnDeck", (scalar)25. / 2.0, UnitSystem_Length_m);
		/*--> Param. nb  3:*/ static const Variables::length DEPTH_AT_BOW("depthAtBow", (scalar)18., UnitSystem_Length_m);
		/*--> Param. nb  4:*/ static const Variables::length DEPTH_AT_TRANSOM("depthAtTransom", (scalar)18., UnitSystem_Length_m);
		/*--> Param. nb  5:*/ static const Variables::length DRAFT("draft", (scalar)6., UnitSystem_Length_m);
		/*--> Param. nb  6:*/ static const Variables::length TRANSOM_HEIGHT("transomHeight", (scalar)8., UnitSystem_Length_m);

		// Stem Dimension Parameters
		/*--> Param. nb  7:*/ static const Variables::realDimless BOW_ROUNDING("bowRounding", (scalar)0.2);
		/*--> Param. nb  8:*/ static const Variables::realDimless FORE_FOOT_SHAPE("foreFootShape", (scalar)1.0);
		/*--> Param. nb  9:*/ static const Variables::angle STEM_RAKE("stemRake", (scalar)30., UnitSystem_Angle_deg);

		/* Forward section Parameters */
		/*--> Param. nb 10:*/ static const Variables::realDimless FWD_TIGHTNESS("fwdTightness", (scalar)0.5);
		/*--> Param. nb 11:*/ static const Variables::realDimless FWD_DEADRISE("fwdDeadRise", (scalar)0.1);
		/*--> Param. nb 12:*/ static const Variables::realDimless FWD_SIDE_SLOPE("fwdSideSlope", (scalar)0.8);
		/*--> Param. nb 13:*/ static const Variables::realDimless FWD_FLARE("fwdFlare", (scalar)0.6);

		/* Midlle section Parameters */
		/*--> Param. nb 14:*/ static const Variables::realDimless MID_TIGHTNESS("midTightness", (scalar)0.5);
		/*--> Param. nb 15:*/ static const Variables::realDimless MID_DEADRISE("midDeadRise", (scalar)0.);
		/*--> Param. nb 16:*/ static const Variables::realDimless MID_SIDE_SLOPE("midSideSlope", (scalar)0.1);
		/*--> Param. nb 17:*/ static const Variables::realDimless MID_FLARE("midFlare", (scalar)0.);

		/* Aft section Parameters */
		/*--> Param. nb 18:*/  static const Variables::realDimless AFT_TIGHTNESS("aftTightness", (scalar)0.5);
		/*--> Param. nb 19:*/  static const Variables::realDimless AFT_DEADRISE("aftDeadRise", (scalar)0.);
		/*--> Param. nb 20:*/  static const Variables::realDimless AFT_SIDE_SLOPE("aftSideSlope", (scalar)0.);
		/*--> Param. nb 21:*/  static const Variables::realDimless AFT_FLARE("aftFlare", (scalar)0.);

		/* Transom Parameters*/
		/*--> Param. nb 22:*/  static const Variables::realDimless TRANSOM_RAKE("transomRake", (scalar)0.);
		/*--> Param. nb 23:*/  static const Variables::realDimless TRANSOM_WIDTH("transomWidth", (scalar)0.6);

		/*keel Parameters*/
		/*--> Param. nb 24:*/  static const Variables::realDimless KEEL_RISE_POINT("keelRisePoint", (scalar)0.);
		/*--> Param. nb 25:*/  static const Variables::realDimless KEEL_POSITION("keelPosition", (scalar)0.5);
		/*--> Param. nb 26:*/  static const Variables::realDimless KEEL_RISE_SLOPE("keelRiseSlope", (scalar)0.3);
		/*--> Param. nb 27:*/  static const Variables::realDimless KELL_TRANSOM_SLOPE("keelTransomSlope", (scalar)0.2);

		/*Hull Parameters*/
		/*--> Param. nb 28:*/  static const Variables::realDimless MAX_AREA_LOCATION("maxAreaLocation", (scalar)0.5);
		/*--> Param. nb 29:*/  static const Variables::realDimless FWD_FULLNESS("fwdFullness", (scalar)0.2);
		/*--> Param. nb 30:*/  static const Variables::realDimless AFT_FULLNESS("aftFullness", (scalar)0.4);

		static const Variables::labelDimless NB_OF_NET_COLUMNS("nbOfNetColumns", 12);
		static const Variables::labelDimless NB_OF_NET_ROWS("nbOfNetRows", 9);
	}
}

#endif // !_DispNo1_DefaultParams_Header

