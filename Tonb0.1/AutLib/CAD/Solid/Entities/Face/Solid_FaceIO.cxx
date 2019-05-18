#include <Solid_Face.hxx>

#include <TecPlot_Opencascade.hxx>

#include <Poly_Triangulation.hxx>

void AutLib::Solid_Face::ExportToPlt
(
	OFstream & File
) const
{
	if (NOT Triangulation()) return;
	Io::ExportMesh(*theTriangulation_, File);
}