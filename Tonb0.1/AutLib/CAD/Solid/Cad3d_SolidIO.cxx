#include <Cad3d_Solid.hxx>

#include <Pnt3d.hxx>
#include <Solid_Vertex.hxx>
#include <Solid_Paired.hxx>
#include <Solid_Face.hxx>
#include <TecPlot.hxx>
#include <TecPlot_Opencascade.hxx>

void AutLib::Cad3d_Solid::ExportToPlt
(
	OFstream & File
) const
{
	ExportVerticesToPlt(File);

	ExportEdgesToPlt(File);

	ExportFreeEdgesToPlt(File);
}

void AutLib::Cad3d_Solid::ExportVerticesToPlt
(
	OFstream & File
) const
{
	if (NOT theVertices_) return;

	std::vector<entity_ptr> entities;
	theVertices_->RetrieveTo(entities);

	std::vector<Pnt3d> Vertices;
	Vertices.reserve(entities.size());

	for (const auto& x : entities)
	{
		Debug_Null_Pointer(std::dynamic_pointer_cast<Solid_Vertex>(x));
		Vertices.push_back(std::dynamic_pointer_cast<Solid_Vertex>(x)->Coord());
	}

	Io::ExportPoints(Vertices, File);
}

void AutLib::Cad3d_Solid::ExportEdgesToPlt
(
	OFstream & File
) const
{
	if (NOT theEdges_) return;

	std::vector<entity_ptr> entities;
	theEdges_->RetrieveTo(entities);

	std::vector<std::shared_ptr<Solid_Paired>> edges;
	edges.reserve(entities.size());

	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(std::dynamic_pointer_cast<Solid_Paired>(x));

		std::dynamic_pointer_cast<Solid_Paired>(x)->ExportToPlt(File);
	}
}

void AutLib::Cad3d_Solid::ExportFacesToPlt
(
	OFstream & File
) const
{
	if (NOT theFaces_) return;

	std::vector<entity_ptr> entities;
	theFaces_->RetrieveTo(entities);

	for (const auto& x : entities)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(std::dynamic_pointer_cast<Solid_Face>(x));

		auto face = std::dynamic_pointer_cast<Solid_Face>(x);

		if (face->Triangulation())
		{
			face->ExportToPlt(File);
		}
	}
}

void AutLib::Cad3d_Solid::ExportFreeEdgesToPlt
(
	OFstream & File
) const
{
	if (NOT theEdges_) return;

	std::vector<paired_ptr> edges;
	RetrieveFreeEdgesTo(edges);

	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);

		x->ExportToPlt(File);
	}
}

void AutLib::Cad3d_Solid::Report
(
	Standard_OStream & Ostream
) const
{
	Ostream << "----------------{ Solid Report }----------------" << std::endl;
	Ostream << std::endl;
	Ostream << "   Name: " << Name() << std::endl;
	Ostream << "   Index: " << Index() << std::endl;
	Ostream << std::endl;
	Ostream << "   Nb. of Vertices: " << NbVertices() << std::endl;
	Ostream << "   Nb. of Edges: " << NbEdges() << std::endl;
	Ostream << "   Nb. of Surfaces: " << NbFaces() << std::endl;
	Ostream << "   Nb. of Holes: " << NbHoles() << std::endl;
	Ostream << std::endl;
	Ostream << "   Has Free Corner? " << (HasFreeEdge() ? "YES" : "NO") << std::endl;
	if (HasFreeEdge()) Ostream << "   Nb. of Free Edges: " << NbFreeEdges() << std::endl;
	Ostream << std::endl;
	Ostream << "-------------{ End of Solid Report }-------------" << std::endl;
}