#pragma once
#ifndef _DispNo1_Parameters_Header
#define _DispNo1_Parameters_Header

#include <Standard_TypeDef.hxx>
#include <Smart_Variable.hxx>

namespace AutLib
{

	class DispNo1_ManipParams
	{

		/*Private Data*/

	protected:

		static Standard_Boolean IsManipulated;

		DispNo1_ManipParams()
		{}

		void SetManipulated()
		{
			if (!IsManipulated)
				IsManipulated = Standard_True;
		}

		void SetUnManipulated()
		{
			IsManipulated = Standard_False;
		}
	};

	class DispNo1_Dimensions
		: public DispNo1_ManipParams
	{

		/*Private Data*/

		Variables::length theDraft_;
		Variables::length theTransomHeight_;

		Variables::length theDepthAtBow_;
		Variables::length theDepthAtTransom_;

		Variables::length theBeamOnDeck_;
		Variables::length theLengthOnDeck_;

		Variables::labelDimless theNbNetRows_;
		Variables::labelDimless theNbNetColumns_;

	public:

		DispNo1_Dimensions();

		DispNo1_Dimensions
		(
			const dictionary& theDict
		);

		const Variables::length& Draft() const
		{
			return theDraft_;
		}

		Variables::length& Draft()
		{
			SetManipulated();
			return theDraft_;
		}

		const Variables::length& TransomHeight() const
		{
			return theTransomHeight_;
		}

		Variables::length& TransomHeight()
		{
			SetManipulated();
			return theTransomHeight_;
		}

		const Variables::length& DepthAtBow() const
		{
			return theDepthAtBow_;
		}

		Variables::length& DepthAtBow()
		{
			SetManipulated();
			return theDepthAtBow_;
		}

		const Variables::length& DepthAtTransom() const
		{
			return theDepthAtTransom_;
		}

		Variables::length& DepthAtTransom()
		{
			SetManipulated();
			return theDepthAtTransom_;
		}

		const Variables::length& BeamOnDeck() const
		{
			return theBeamOnDeck_;
		}

		Variables::length& BeamOnDeck()
		{
			SetManipulated();
			return theBeamOnDeck_;
		}

		const Variables::length& LengthOnDeck() const
		{
			return theLengthOnDeck_;
		}

		Variables::length& LengthOnDeck()
		{
			SetManipulated();
			return theLengthOnDeck_;
		}

		const Variables::labelDimless& NbNetRows() const
		{
			return theNbNetRows_;
		}

		Variables::labelDimless& NbNetRows()
		{
			SetManipulated();
			return theNbNetRows_;
		}

		const Variables::labelDimless& NbNetColumns() const
		{
			return theNbNetColumns_;
		}

		Variables::labelDimless& NbNetColumns()
		{
			SetManipulated();
			return theNbNetColumns_;
		}
	};


	class DispNo1_SectionParamsBase
		: public DispNo1_ManipParams
	{

		/*Private Data*/

		Variables::realDimless theTightness_;
		Variables::realDimless theDeadRise_;
		Variables::realDimless theSideSlope_;
		Variables::realDimless theFlare_;

	public:

		DispNo1_SectionParamsBase
		(
			const Variables::realDimless& theTightness,
			const Variables::realDimless& theDeadrise,
			const Variables::realDimless& theSideSlope,
			const Variables::realDimless& theFlare
		)
			: theTightness_(theTightness)
			, theDeadRise_(theDeadrise)
			, theSideSlope_(theSideSlope)
			, theFlare_(theFlare)
		{}

		DispNo1_SectionParamsBase
		(
			const dictionary& theDict
		);

		const Variables::realDimless& Tightness() const
		{
			return theTightness_;
		}

		Variables::realDimless& Tightness()
		{
			SetManipulated();
			return theTightness_;
		}

		const Variables::realDimless& DeadRise() const
		{
			return theDeadRise_;
		}

		Variables::realDimless& DeadRise()
		{
			SetManipulated();
			return theDeadRise_;
		}

		const Variables::realDimless& SideSlope() const
		{
			return theSideSlope_;
		}

		Variables::realDimless& SideSlope()
		{
			SetManipulated();
			return theSideSlope_;
		}

		const Variables::realDimless& Flare() const
		{
			return theFlare_;
		}

		Variables::realDimless& Flare()
		{
			SetManipulated();
			return theFlare_;
		}
	};

	class DispNo1_AftSectionParams
		: public DispNo1_SectionParamsBase
	{

	public:

		DispNo1_AftSectionParams();

		DispNo1_AftSectionParams
		(
			const dictionary& theDict
		);

	};


	class DispNo1_MidSectionParams
		: public DispNo1_SectionParamsBase
	{

	public:

		DispNo1_MidSectionParams();

		DispNo1_MidSectionParams
		(
			const dictionary& theDict
		);

	};


	class DispNo1_FwdSectionParams
		: public DispNo1_SectionParamsBase
	{

	public:

		DispNo1_FwdSectionParams();

		DispNo1_FwdSectionParams
		(
			const dictionary& theDict
		);

	};


	class DispNo1_KeelParams
		: public DispNo1_ManipParams
	{

		/*Private Data*/

		Variables::realDimless thePosition_;
		Variables::realDimless theRisePoint_;
		Variables::realDimless theRiseSlope_;
		Variables::realDimless theTransomSlope_;

	public:

		DispNo1_KeelParams();

		DispNo1_KeelParams
		(
			const dictionary& theDict
		);


		const Variables::realDimless& Position() const
		{
			return thePosition_;
		}

		Variables::realDimless& Position()
		{
			SetManipulated();
			return thePosition_;
		}

		const Variables::realDimless& RisePoint() const
		{
			return theRisePoint_;
		}

		Variables::realDimless& RisePoint()
		{
			SetManipulated();
			return theRisePoint_;
		}

		const Variables::realDimless& RiseSlope() const
		{
			return theRiseSlope_;
		}

		Variables::realDimless& RiseSlope()
		{
			SetManipulated();
			return theRiseSlope_;
		}

		const Variables::realDimless& TransomSlope() const
		{
			return theTransomSlope_;
		}

		Variables::realDimless& TransomSlope()
		{
			SetManipulated();
			return theTransomSlope_;
		}
	};


	class DispNo1_StemParams
		: public DispNo1_ManipParams
	{

		/*Private Data*/

		Variables::realDimless theBowRounding_;
		Variables::angle theStemRake_;
		Variables::realDimless theForeFootShape_;

	public:

		DispNo1_StemParams();

		DispNo1_StemParams
		(
			const dictionary& theDict
		);


		const Variables::realDimless& BowRounding() const
		{
			return theBowRounding_;
		}

		Variables::realDimless& BowRounding()
		{
			SetManipulated();
			return theBowRounding_;
		}

		const Variables::angle& StemRake() const
		{
			return theStemRake_;
		}

		Variables::angle& StemRake()
		{
			SetManipulated();
			return theStemRake_;
		}

		const Variables::realDimless& ForeFootShape() const
		{
			return theForeFootShape_;
		}

		Variables::realDimless& ForeFootShape()
		{
			SetManipulated();
			return theForeFootShape_;
		}
	};

	class DispNo1_TransomParams
		: public DispNo1_ManipParams
	{

		/*Private Data*/

		Variables::realDimless theRake_;
		Variables::realDimless theWidth_;

	public:

		DispNo1_TransomParams();

		DispNo1_TransomParams(const dictionary& theDict);

		const Variables::realDimless& Rake() const
		{
			return theRake_;
		}

		Variables::realDimless& Rake()
		{
			SetManipulated();
			return theRake_;
		}

		const Variables::realDimless& Width() const
		{
			return theWidth_;
		}

		Variables::realDimless& Width()
		{
			SetManipulated();
			return theWidth_;
		}
	};


	class DispNo1_HullParams
		: public DispNo1_ManipParams
	{

		/*Private Data*/

		DispNo1_AftSectionParams theAft_;
		DispNo1_MidSectionParams theMid_;
		DispNo1_FwdSectionParams theFwd_;

		Variables::realDimless theMaxAreaLocation_;
		Variables::realDimless theFwdFullness_;
		Variables::realDimless theAftFullness_;

	public:

		DispNo1_HullParams();

		DispNo1_HullParams
		(
			const dictionary& theDict
		);


		const DispNo1_AftSectionParams& AftSection() const
		{
			return theAft_;
		}

		DispNo1_AftSectionParams& AftSection()
		{
			SetManipulated();
			return theAft_;
		}

		const DispNo1_MidSectionParams& MidSection() const
		{
			return theMid_;
		}

		DispNo1_MidSectionParams& MidSection()
		{
			SetManipulated();
			return theMid_;
		}

		const DispNo1_FwdSectionParams& FwdSection() const
		{
			return theFwd_;
		}

		DispNo1_FwdSectionParams& FwdSection()
		{
			SetManipulated();
			return theFwd_;
		}

		const Variables::realDimless& MaxAreaLocation() const
		{
			return theMaxAreaLocation_;
		}

		Variables::realDimless& MaxAreaLocation()
		{
			SetManipulated();
			return theMaxAreaLocation_;
		}

		const Variables::realDimless& FwdFullness() const
		{
			return theFwdFullness_;
		}

		Variables::realDimless& FwdFullness()
		{
			SetManipulated();
			return theFwdFullness_;
		}

		const Variables::realDimless& AftFullness() const
		{
			return theAftFullness_;
		}

		Variables::realDimless& AftFullness()
		{
			SetManipulated();
			return theAftFullness_;
		}
	};

	class DispNo1_Parameters
		: public DispNo1_Dimensions
		, public DispNo1_HullParams
		, public DispNo1_StemParams
		, public DispNo1_KeelParams
		, public DispNo1_TransomParams
	{

		/*Private Data*/

	public:

		DispNo1_Parameters()
		{}

		DispNo1_Parameters
		(
			const dictionary& theDict
		)
			: DispNo1_Dimensions(theDict)
			, DispNo1_HullParams(theDict)
			, DispNo1_StemParams(theDict)
			, DispNo1_KeelParams(theDict)
			, DispNo1_TransomParams(theDict)
		{}

	};
}

#endif // !_DispNo1_Parameters_Header
