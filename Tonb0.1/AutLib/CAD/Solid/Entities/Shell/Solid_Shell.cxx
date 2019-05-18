#include <Solid_Shell.hxx>

#include <Entity3d_Box.hxx>
#include <Solid_Face.hxx>

void AutLib::Solid_Shell::CloseCondition()
{
	Debug_Null_Pointer(theFaces_);
	const auto& faces = *theFaces_;

	for (const auto& x : faces)
	{
		Debug_Null_Pointer(x);

		if (NOT x->IsClamped())
		{
			IsClosed_ = Standard_False;
			return;
		}
	}
	IsClosed_ = Standard_True;
}

void AutLib::Solid_Shell::CalcBoundingBox()
{
	Debug_Null_Pointer(theFaces_);
	const auto& faces = *theFaces_;

	auto box = *faces[0]->BoundingBox();
	for (int i = 1; i < faces.size(); i++)
	{
		Debug_Null_Pointer(faces[i]->BoundingBox());

		box = Entity3d_Box::Union(box, *faces[i]->BoundingBox());
	}

	theBoundingBox_ = std::make_shared<Entity3d_Box>(box);
}