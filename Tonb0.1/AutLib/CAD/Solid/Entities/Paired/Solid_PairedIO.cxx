#include <Solid_Paired.hxx>

#include <Entity3d_Polygon.hxx>

void AutLib::Solid_Paired::ExportToPlt(OFstream & File) const
{
	if (theMesh_)
	{
		theMesh_->ExportToPlt(File);
	}
}