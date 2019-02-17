#pragma once
#ifndef _DispNo1_Profiles_Header
#define _DispNo1_Profiles_Header

#include <Standard_Handle.hxx>
#include <Geom2d_Curve.hxx>
#include <TColgp_Array2OfPnt.hxx>

#include <Stl_Vector.hxx>
#include <Pnt3d.hxx>
#include <DispNo1_Dim.hxx>

#include <memory>

namespace AutLib
{

	typedef Handle(Geom2d_Curve) ParameterProfile;

	typedef Stl_Vector<ParameterProfile> ParameterProfileList;

	struct DispNo1_Profile
	{

		ParameterProfile Deck;
		ParameterProfile Buttock;

		ParameterProfileList Flares;
		ParameterProfileList Sections;

	protected:

		void AllocateMemory
		(
			const Standard_Integer n
		)
		{
			if (NOT INSIDE(n, DispNo1::MIN_NB_SECTIONS, DispNo1::MAX_NB_SECTIONS))
			{
				FatalErrorIn("void AllocateMemory(const Standard_Integer n)")
					<< " Invalid Nb of Sections; nb. of Sections = " << n << endl
					<< " Min nb. of sections = " << DispNo1::MIN_NB_SECTIONS << endl
					<< " Max nb. of sections = " << DispNo1::MAX_NB_SECTIONS << endl
					<< abort(FatalError);
			}

			Flares.resize(n);
			Sections.resize(n);
		}
	};


	typedef Stl_Vector<Pnt3d> pointList;
	typedef Stl_Vector<Standard_Real> realList;

	struct DispNo1_SectionCtrlPts
	{

		Standard_Integer Corner;

		pointList CtrlPts;
	};


	typedef std::shared_ptr<DispNo1_SectionCtrlPts> sectionCtrlPtsPtr;
	typedef Stl_Vector<sectionCtrlPtsPtr> sectionCtrlPtsList;

	struct DispNo1_Xparams
	{

		realList xXCoords;
		realList xYCoords;
		realList xZCoords;

		realList xDepth;
		realList xSheer;

		realList xTightness;
		realList xFlare;
		realList xDeadRise;
		realList xSideSlope;
		realList xSideSlopeAngle;

		realList xRake;

		sectionCtrlPtsList xSection;

	protected:

		void AllocateMemory
		(
			const Standard_Integer n
		)
		{
			if (NOT INSIDE(n, DispNo1::MIN_NB_SECTIONS, DispNo1::MAX_NB_SECTIONS))
			{
				FatalErrorIn("void AllocateMemory(const Standard_Integer n)")
					<< " Invalid Nb of Sections; nb. of Sections = " << n << endl
					<< " Min nb. of sections = " << DispNo1::MIN_NB_SECTIONS << endl
					<< " Max nb. of sections = " << DispNo1::MAX_NB_SECTIONS << endl
					<< abort(FatalError);
			}

			xXCoords.resize(n);
			xYCoords.resize(n);
			xZCoords.resize(n);

			xDepth.resize(n);
			xSheer.resize(n);

			xTightness.resize(n);
			xFlare.resize(n);
			xDeadRise.resize(n);
			xSideSlope.resize(n);
			xSideSlopeAngle.resize(n);

			xRake.resize(n);

			xSection.resize(n);
		}
	};

	typedef TColgp_Array2OfPnt ctrlNet;
	typedef std::shared_ptr<TColgp_Array2OfPnt> ctrlNetPtr;

	struct DispNo1_CtrlNet
	{

		ctrlNetPtr CtrlNet;
	};
}

#endif // !_DispNo1_Profiles_Header
