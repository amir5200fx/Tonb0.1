#include <Solid_Edge.hxx>

#include <Solid_Ring.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <BRep_Tool.hxx>

void AutLib::Solid_Edge::CheckEdge()
{
	if (!theStart_)
	{
		FatalErrorIn("void AutLib::Solid_Edge::CheckEdge()")
			<< "Null Pointer encountered: theStart_" << endl
			<< abort(FatalError);
	}

	if (!theEnd_)
	{
		FatalErrorIn("void AutLib::Solid_Edge::CheckEdge()")
			<< "Null Pointer encountered: theEnd_" << endl
			<< abort(FatalError);
	}

	if (!thePar_)
	{
		FatalErrorIn("void AutLib::Solid_Edge::CheckEdge()")
			<< "Null Pointer encountered: thePar_" << endl
			<< abort(FatalError);
	}

	if (!theCurve_)
	{
		FatalErrorIn("void AutLib::Solid_Edge::CheckEdge()")
			<< "Null Pointer encountered: theCurve_" << endl
			<< abort(FatalError);
	}
}

Standard_Boolean AutLib::Solid_Edge::IsDegenerated() const
{
	return BRep_Tool::Degenerated(theTEdge_);
}

Standard_Boolean AutLib::Solid_Edge::IsRing() const
{
	return (Standard_Boolean)std::dynamic_pointer_cast<Solid_Ring>(std::const_pointer_cast<Solid_Edge>(This()));
}