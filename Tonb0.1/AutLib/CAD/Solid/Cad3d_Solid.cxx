#include <Cad3d_Solid.hxx>

#include <Entity3d_Box.hxx>
#include <Solid_Paired.hxx>
#include <Solid_Face.hxx>
#include <Solid_Shell.hxx>
#include <Solid_BlockEntity.hxx>
#include <Solid_EntityManager.hxx>
#include <Cad3d_SolidTools.hxx>

namespace AutLib
{
	typedef std::shared_ptr<Solid_BlockEntity> block_ptr;
	typedef std::vector<block_ptr> blockList;

	const Standard_Real Cad3d_SolidInfo::DEFAULT_TOLERANCE = (Standard_Real)1.0E-4;
}

void AutLib::Cad3d_Solid::CalcBoundingBox
(
	const faceList& theFaces
)
{
	if (theFaces.empty())
	{
		FatalErrorIn("void AutLib::Cad3d_Solid::CalcBoundingBox()")
			<< "the solid has no face!" << endl
			<< abort(FatalError);
	}

	Debug_Null_Pointer(theFaces[0]);
	Debug_Null_Pointer(theFaces[0]->BoundingBox());

	auto box = *theFaces[0]->BoundingBox();
	for (int i = 1; i < theFaces.size(); i++)
	{
		Debug_Null_Pointer(theFaces[i]);
		Debug_Null_Pointer(theFaces[i]->BoundingBox());

		box = Entity3d_Box::Union(box, *theFaces[i]->BoundingBox());
	}
	theBoundingBox_ = std::make_shared<Entity3d_Box>(box);
}

Standard_Boolean 
AutLib::Cad3d_Solid::MakeShells
(
	const faceList & theFaces
)
{
	auto Shells_ptr = 
		Cad3d_SolidTools::TrackShells(theFaces);

	auto& Shells = *Shells_ptr;

	for (const auto& x : Shells)
	{
		Debug_Null_Pointer(x);

		if (NOT x->IsClosed())
		{
			theInner_ = Shells_ptr;
			return Standard_True;
		}
	}

	theInner_ = std::make_shared<shellList>();
	if (Cad3d_SolidTools::InnerHoles(Shells, *theInner_, theOutter_))
	{
		return Standard_True;
	}
	return Standard_False;
}

void AutLib::Cad3d_Solid::SplitByShells()
{
	if (theFaces_->NbBlocks() > 1)
	{
		theFaces_->CompactBlocks("Default Block Surface");
	}

	if (theFaces_->NbBlocks() NOT_EQUAL 1)
	{
		FatalErrorIn("void AutLib::Cad3d_Solid::SplitByShells()")
			<< "Invalid Data" << endl
			<< abort(FatalError);
	}

	Debug_Null_Pointer(theInner_);
	if (theInner_->empty())
	{
		return;
	}

	blockList blocks;
	theFaces_->RetrieveTo(blocks);

	Debug_If_Condition_Message(blocks.size() NOT_EQUAL 1, "Conflict Data");
	const auto& block = theFaces_->SelectBlockEntity(blocks[0]->Name());

	const auto& InnerShells = *theInner_;
	Standard_Integer K = 0;
	for (const auto& x : InnerShells)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(x->Faces());

		const auto& faces = *x->Faces();
		for (const auto& face : faces)
		{
			Debug_Null_Pointer(face);
			block->SelectEntity(face->Index());
		}

		theFaces_->Split("Default Inner Shell " + std::to_string((++K) + 1));
	}

	if (NOT block->NbEntities())
	{
		FatalErrorIn("void AutLib::Cad3d_Solid::SplitByShells()")
			<< "Conflict Data"
			<< abort(FatalError);
	}
}

Standard_Integer AutLib::Cad3d_Solid::NbFreeEdges() const
{
	Debug_Null_Pointer(theEdges_);

	Standard_Integer K = 0;
	std::vector<entity_ptr> edges;
	theEdges_->RetrieveTo(edges);

	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(std::dynamic_pointer_cast<Solid_Paired>(x));

		if (NOT std::dynamic_pointer_cast<Solid_Paired>(x)->IsPaired()) ++K;
	}
	return K;
}

Standard_Boolean AutLib::Cad3d_Solid::HasFreeEdge() const
{
	Debug_Null_Pointer(theEdges_);

	std::vector<entity_ptr> edges;
	theEdges_->RetrieveTo(edges);

	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(std::dynamic_pointer_cast<Solid_Paired>(x));

		if (NOT std::dynamic_pointer_cast<Solid_Paired>(x)->IsPaired()) return Standard_True;
	}
	return Standard_False;
}

void AutLib::Cad3d_Solid::RetrieveFreeEdgesTo
(
	std::vector<paired_ptr>& theEdges
) const
{
	Debug_Null_Pointer(theEdges_);

	std::vector<entity_ptr> edges;
	theEdges_->RetrieveTo(edges);

	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);

		auto paired = std::dynamic_pointer_cast<Solid_Paired>(x);
		if (paired) theEdges.push_back(paired);
	}
}