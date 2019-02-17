#pragma once
#ifndef _Vessels_DispNo1_Header
#define _Vessels_DispNo1_Header

#include <Global_Macros.hxx>
#include <Model_Entity.hxx>
#include <DispNo1_Parameters.hxx>
#include <DispNo1_Profiles.hxx>
#include <Vessels_Displacements.hxx>

class Geom_Surface;

namespace AutLib
{

	class DispNo1Base
	{

		/*Private Data*/

		Standard_Boolean ApplySmoothing_;

	public:

		DispNo1Base()
			: ApplySmoothing_(Standard_True)
		{}

		Standard_Boolean ApplySmoothing() const
		{
			return ApplySmoothing_;
		}

		Standard_Boolean& ApplySmoothing()
		{
			return ApplySmoothing_;
		}
	};


	class DispNo1_Memory
		: public DispNo1_Profile
		, public DispNo1_Xparams
		, public DispNo1_CtrlNet
	{

		/*Private Data*/

	public:

		DispNo1_Memory()
		{}
	};

	class DispNo1_HullPatch
		: public Vessels_Displacements
		, public DispNo1_Parameters
		, public DispNo1Base
		, public DispNo1_Memory
	{

		typedef Handle(Geom_Surface) HullSurface;

		typedef Vessels_Displacements entity;
		typedef DispNo1_Parameters params;
		typedef DispNo1Base base;
		typedef DispNo1_Memory memory;

		/*Private Data*/

		HullSurface theHull_;


		// Private functions and operators

		void AllocateMemory();

		// Create Profiles

		void CreateDeckProfile();

		void CreateFlareProfile
		(
			const Standard_Integer theSection
		);

		void CreateFlareProfile();


		// Calculate Parameters

		void CalcxXSections();

		void CalcxYSections();

		void CalcxZSections();

		void CalcxDepthSections();

		void CalcxDeadRise();

		void CalcxFlare();

		void CalcxSideSlope();

		void CalcxTightness();

		void CalcxRake();

		void CalcXSheer();

		void CalcxParameters();


		// Apply Parameters

		void ApplyTightness();

		void ApplyFlare();

		void ApplyRake();

		void ApplyForeFootShape();

		void ApplyBowSmoothness();

		void ApplyParameters();

		void ApplyTightness
		(
			DispNo1_SectionCtrlPts& Section,
			const Standard_Real Tightness
		);

		void ApplyFlare
		(
			Standard_Integer Section
		);

		void ApplyRake
		(
			DispNo1_SectionCtrlPts& Section,
			const Standard_Real Rake
		);


		// Section constructors

		std::shared_ptr<DispNo1_SectionCtrlPts> CreateRawSection
		(
			const Standard_Integer Section,
			const Standard_Integer nbWidth,
			const Standard_Integer nbHeight
		);

		std::shared_ptr<DispNo1_SectionCtrlPts> CreateRawStem() const;

		std::shared_ptr<DispNo1_SectionCtrlPts> CreateRawStemPaired();

		void CreateRawSections();


		// Setup hull

		void SetupControlNet();

		void SetupPatch();

		void SetSection
		(
			const Standard_Integer Index,
			const std::shared_ptr<DispNo1_SectionCtrlPts>& Section
		)
		{
			xSection[Index] = Section;
		}

		void SetControlPoint
		(
			const Standard_Integer I,
			const Standard_Integer J,
			const Pnt3d & Coord
		)
		{
			CtrlNet->SetValue(I + 1, J + 1, Coord);
		}


		DisallowBitWiseCopy(DispNo1_HullPatch);

	protected:

		virtual void MakeFace();

	public:

		DispNo1_HullPatch()
		{}


		DispNo1_HullPatch(const dictionary& theDict);

		Standard_Boolean IsDone() const override
		{
			if (IsManipulated AND NOT IsDone())
				IsDone_ = Standard_False;
			return IsDone_;
		}

		virtual void Perform();

		const HullSurface& Patch() const
		{
			return theHull_;
		}

		const DispNo1_Parameters& Parameters() const
		{
			return *this;
		}

		DispNo1_Parameters& Parameters()
		{
			return *this;
		}

		const DispNo1_Parameters& Dimensions() const
		{
			return *this;
		}

		DispNo1_Parameters& Dimensions()
		{
			return *this;
		}

		const DispNo1_Xparams& Xparams() const
		{
			return *this;
		}

		TopoDS_Shape GetStation(const Standard_Real theX) const;

		TopoDS_Shape GetButtock(const Standard_Real theY) const;

		TopoDS_Shape GetWater(const Standard_Real theZ) const;

	};


	class DispNo1_BareHull
		: public DispNo1_HullPatch
	{

		/*Private Data*/

	protected:

		void MakeFace() override;

	public:

		DispNo1_BareHull()
		{}

		const DispNo1_HullPatch& Half() const
		{
			return *this;
		}

	};
}

#endif // !_Vessels_DispNo1_Header
