#include <Cad3d_SolidTools.hxx>

#include <Adt_AvlTree.hxx>
#include <Entity3d_Box.hxx>
#include <Solid_Shell.hxx>
#include <error.hxx>
#include <OSstream.hxx>

namespace AutLib
{

	typedef std::shared_ptr<Solid_Shell> shell_ptr;

	static shell_ptr RetrieveShell
	(
		Adt_AvlTree<shell_ptr>& theRegister
	)
	{
		if (theRegister.IsEmpty())
		{
			FatalErrorIn("shell_ptr RetrieveShell(Adt_AvlTree<shell_ptr>& theRegister)")
				<< "Empty tree" << endl
				<< abort(FatalError);
		}

		shell_ptr root;
		theRegister.Root(root);
		theRegister.Remove(root);

		return std::move(root);
	}

	static void IdentifyHoles
	(
		const shell_ptr& InnerCandidate,
		const shell_ptr& OuterCandidate,
		std::vector<shell_ptr>& QInners,
		shell_ptr& theOuter
	)
	{
		if (InnerCandidate)
			QInners.push_back(InnerCandidate);

		if (theOuter)
		{
			Debug_Null_Pointer(OuterCandidate->BoundingBox());
			Debug_Null_Pointer(theOuter->BoundingBox());

			if (Entity3d_Box::IsInside(*OuterCandidate->BoundingBox(), *theOuter->BoundingBox()))
			{
				QInners.push_back(OuterCandidate);
			}
			else
			{
				QInners.push_back(theOuter);
				theOuter = OuterCandidate;
			}
		}
		else
		{
			theOuter = OuterCandidate;
		}
	}

	static void TrackHoles
	(
		Adt_AvlTree<shell_ptr>& theRegister,
		std::vector<shell_ptr>& QInners,
		shell_ptr& theOuter
	)
	{
		if (theRegister.IsEmpty()) return;

		shell_ptr Outer;
		shell_ptr Inner;

		Outer = RetrieveShell(theRegister);

		if (theRegister.IsEmpty())
		{
			IdentifyHoles(nullptr, Outer, QInners, theOuter);
			return;
		}

		Inner = RetrieveShell(theRegister);

		Debug_Null_Pointer(Outer->BoundingBox());
		Debug_Null_Pointer(Inner->BoundingBox());

		const auto& OuterBox = *Outer->BoundingBox();
		const auto& InnerBox = *Inner->BoundingBox();

		if (Entity3d_Box::IsInside(InnerBox, OuterBox))
		{
			IdentifyHoles(Inner, Outer, QInners, theOuter);

			TrackHoles(theRegister, QInners, theOuter);
		}
		else if (Entity3d_Box::IsInside(OuterBox, InnerBox))
		{
			IdentifyHoles(Outer, Inner, QInners, theOuter);

			TrackHoles(theRegister, QInners, theOuter);
		}
		else
		{
			QInners.push_back(Inner);
			QInners.push_back(Outer);

			TrackHoles(theRegister, QInners, theOuter);
		}
	}
}

Standard_Boolean 
AutLib::Cad3d_SolidTools::InnerHoles
(
	const shellList & theShells,
	shellList & theInners, 
	shell_ptr & theOuter
)
{
	if (theShells.empty())
	{
		FatalErrorIn("void InnerHoles(const shellList& theShells, shellList& theInners, shellList& theOuters)")
			<< "Empty shell list!" << endl
			<< abort(FatalError);
	}

	Adt_AvlTree<std::shared_ptr<Solid_Shell>> Register;
	Register.SetComparableFunction(&Solid_Shell::IsLess);

	Register.Insert(theShells);

	TrackHoles(Register, theInners, theOuter);

	if (NOT theOuter) return Standard_True;
	return Standard_False;
}