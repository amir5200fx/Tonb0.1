#pragma once
#ifndef _DispNo1_Parameters_Header
#define _DispNo1_Parameters_Header

#include <Standard_TypeDef.hxx>
#include <Smart_Variable.hxx>

namespace AutLib
{

	namespace DispNo1
	{

		class ManipParams
		{

			/*Private Data*/

		protected:

			static Standard_Boolean IsManipulated;

			ManipParams()
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

		class Dimensions
			: public ManipParams
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

			Dimensions();

			Dimensions
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


		class SectionParamsBase
			: public ManipParams
		{

			/*Private Data*/

			Variables::realDimless theTightness_;
			Variables::realDimless theDeadRise_;
			Variables::realDimless theSideSlope_;
			Variables::realDimless theFlare_;

		public:

			SectionParamsBase();

			SectionParamsBase
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

		class AftSectionParams
			: public SectionParamsBase
		{

		public:

			AftSectionParams();

			AftSectionParams
			(
				const dictionary& theDict
			);
			
		};


		class MidSectionParams
			: public SectionParamsBase
		{

		public:

			MidSectionParams();

			MidSectionParams
			(
				const dictionary& theDict
			);

		};


		class FwdSectionParams
			: public SectionParamsBase
		{

		public:

			FwdSectionParams();

			FwdSectionParams
			(
				const dictionary& theDict
			);

		};


		class KeelParams
			: public ManipParams
		{

			/*Private Data*/

			Variables::realDimless thePosition_;
			Variables::realDimless theRisePoint_;
			Variables::realDimless theRiseSlope_;
			Variables::realDimless theTransomSlope_;

		public:

			KeelParams();

			KeelParams
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


		class StemParams
			: public ManipParams
		{

			/*Private Data*/

			Variables::realDimless theBowRounding_;
			Variables::angle theStemRake_;
			Variables::realDimless theForeFootShape_;

		public:

			StemParams();

			StemParams
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

		class TransomParams
			: public ManipParams
		{

			/*Private Data*/

			Variables::realDimless theRake_;
			Variables::realDimless theWidth_;

		public:

			TransomParams();

			TransomParams(const dictionary& theDict);

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


		class HullParams
			: public ManipParams
		{

			/*Private Data*/

			AftSectionParams theAft_;
			MidSectionParams theMid_;
			FwdSectionParams theFwd_;

			Variables::realDimless theMaxAreaLocation_;
			Variables::realDimless theFwdFullness_;
			Variables::realDimless theAftFullness_;

		public:

			HullParams();

			HullParams
			(
				const dictionary& theDict
			);


			const AftSectionParams& AftSection() const
			{
				return theAft_;
			}

			AftSectionParams& AftSection()
			{
				SetManipulated();
				return theAft_;
			}

			const MidSectionParams& MidSection() const
			{
				return theMid_;
			}

			MidSectionParams& MidSection()
			{
				SetManipulated();
				return theMid_;
			}

			const FwdSectionParams& FwdSection() const
			{
				return theFwd_;
			}

			FwdSectionParams& FwdSection()
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

		class Parameters
			: public Dimensions
			, public HullParams
			, public StemParams
			, public KeelParams
			, public TransomParams
		{

			/*Private Data*/

		public:

			Parameters()
			{}

			Parameters
			(
				const dictionary& theDict
			)
				: Dimensions(theDict)
				, HullParams(theDict)
				, StemParams(theDict)
				, KeelParams(theDict)
				, TransomParams(theDict)
			{}

		};
	}
}

#endif // !_DispNo1_Parameters_Header
