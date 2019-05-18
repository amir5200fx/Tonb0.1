#include <Solid_Face.hxx>

#include <Pnt3d.hxx>
#include <Entity2d_Box.hxx>
#include <Entity3d_Box.hxx>

#include <Bnd_Box.hxx>
#include <BRepBndLib.hxx>
#include <Solid_Edge.hxx>
#include <Solid_Wire.hxx>

AutLib::Solid_Face::edgeList
AutLib::Solid_Face::Edges() const
{
	Debug_Null_Pointer(theOuter_);

	Standard_Integer size = theOuter_->NbEdges();
	if (theInner_)
	{
		const auto& Inner = *theInner_;
		for (const auto& x : Inner)
			size += x->NbEdges();
	}

	edgeList List;
	List.reserve(size);

	Debug_Null_Pointer(theOuter_->Edges());
	const auto& OuterEdges = *theOuter_->Edges();

	for (const auto& x : OuterEdges)
	{
		List.push_back(x);
	}

	if (!theInner_) return std::move(List);

	const auto& Inner = *theInner_;
	for (const auto& x : Inner)
	{
		Debug_Null_Pointer(x->Edges());
		const auto& Edges = *x->Edges();
		for (const auto& edge : Edges)
			List.push_back(edge);
	}

	return std::move(List);
}

Standard_Boolean AutLib::Solid_Face::IsClamped() const
{
	Debug_Null_Pointer(theOuter_);
	Debug_Null_Pointer(theOuter_->Edges());
	const auto& OuterEdges = *theOuter_->Edges();

	for (const auto& x : OuterEdges)
	{
		Debug_Null_Pointer(x);

		if (NOT x->PairedEdge().lock()) return Standard_False;
	}
	return Standard_True;
}

AutLib::Entity2d_Box 
AutLib::Solid_Face::CalcParametricBoundingBox() const
{
	Debug_Null_Pointer(theOuter_);
	return theOuter_->CalcParametricBoundingBox();
}

void AutLib::Solid_Face::CalcBoundingBox()
{
	if (TFace().IsNull())
	{
		FatalErrorIn("void AutLib::Solid_Face::CalcBoundingBox()")
			<< "No FACE info has been set" << endl
			<< abort(FatalError);
	}

	Bnd_Box box;
	BRepBndLib::Add(TFace(), box);

	Standard_Real xmin, xmax, ymin, ymax, zmin, zmax;
	box.Get(xmin, ymin, zmin, xmax, ymax, zmax);

	theBoundingBox_ = 
		std::make_shared<Entity3d_Box>
		(
			Pnt3d(xmin, ymin, zmin),
			Pnt3d(xmax, ymax, zmax)
			);
}