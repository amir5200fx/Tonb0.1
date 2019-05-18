#include <Cad3d_SolidTools.hxx>

#include <Adt_AvlTree.hxx>
#include <Solid_Edge.hxx>
#include <Solid_Paired.hxx>
#include <Solid_Face.hxx>
#include <Solid_Shell.hxx>
#include <error.hxx>
#include <OSstream.hxx>

namespace AutLib
{
	
	static void TrackShell
	(
		const std::shared_ptr<Solid_Face>& theFace, 
		Adt_AvlTree<std::shared_ptr<Solid_Face>>& theRegister,
		std::vector<std::shared_ptr<Solid_Face>>& theList
	)
	{
		Debug_Null_Pointer(theFace);
		const auto& face = *theFace;

		const auto Edges = face.Edges();
		for (const auto& x : Edges)
		{
			Debug_Null_Pointer(x);

			if (x->IsDegenerated()) continue;

			const auto& paired = x->PairedEdge().lock();

			if (NOT paired) continue;
			Debug_Null_Pointer(paired);

			const auto& neighbor = paired->Face().lock();
			Debug_Null_Pointer(neighbor);

			if (neighbor NOT_EQUAL theFace AND theRegister.IsContains(neighbor))
			{
				theRegister.Remove(neighbor);
				theList.push_back(neighbor);

				TrackShell(neighbor, theRegister, theList);
			}
		}
	}

	static 
		std::shared_ptr<std::vector<std::shared_ptr<Solid_Face>>>
		TrackShell
	(
		Adt_AvlTree<std::shared_ptr<Solid_Face>>& theRegister
	)
	{
		if (theRegister.IsEmpty())
		{
			FatalErrorIn("void TrackShell()")
				<< "The register container is empty" << endl
				<< abort(FatalError);
		}

		auto list_ptr = std::make_shared<std::vector<std::shared_ptr<Solid_Face>>>();
		auto& list = *list_ptr;

		std::shared_ptr<Solid_Face> root;
		theRegister.Root(root);

		list.push_back(root);

		theRegister.Remove(root);

		TrackShell(root, theRegister, list);

		return std::move(list_ptr);
	}
}

std::shared_ptr<AutLib::Cad3d_SolidTools::shellList>
AutLib::Cad3d_SolidTools::TrackShells
(
	const faceList & theFaces
)
{
	if (theFaces.size() < 1)
	{
		FatalErrorIn("shellList TrackShells(const faceList& theFaces)")
			<< "Empty list" << endl
			<< abort(FatalError);
	}

	auto Edges = RetrieveEdges(theFaces);

	Adt_AvlTree<std::shared_ptr<Solid_Face>> Register;
	Register.SetComparableFunction(&Solid_Face::IsLess);

	Register.Insert(theFaces);

	Standard_Integer K = 0;
	auto List_ptr = std::make_shared<shellList>();
	auto& List = *List_ptr;
	while (NOT Register.IsEmpty())
	{
		List.push_back(std::make_shared<Solid_Shell>(++K, TrackShell(Register)));
	}

	return std::move(List_ptr);
}