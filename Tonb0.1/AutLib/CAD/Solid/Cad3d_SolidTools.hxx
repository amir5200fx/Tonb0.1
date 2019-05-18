#pragma once
#ifndef _Cad3d_SolidTools_Header
#define _Cad3d_SolidTools_Header

#include <Standard_TypeDef.hxx>
#include <Entity3d_TriangulationFwd.hxx>
#include <OFstream.hxx>

class TopoDS_Shape;
class TopoDS_Vertex;
class TopoDS_Edge;
class TopoDS_Face;
class TopoDS_Solid;

#include <memory>
#include <vector>

namespace AutLib
{

	// Forward Declarations
	class Solid_Edge;
	class Solid_Face;
	class Solid_Shell;
	class Cad3d_Solid;

	class Cad3d_SolidTools
	{

	public:

		typedef std::shared_ptr<Solid_Edge> edge_ptr;
		typedef std::shared_ptr<Solid_Face> face_ptr;
		typedef std::shared_ptr<Solid_Shell> shell_ptr;
		typedef std::vector<edge_ptr> edgeList;
		typedef std::vector<face_ptr> faceList;
		typedef std::vector<shell_ptr> shellList;
		typedef std::shared_ptr<Entity3d_Triangulation> triangulation3d_ptr;
		typedef std::vector<triangulation3d_ptr> triangulation3dList;
		typedef std::shared_ptr<Cad3d_Solid> solid_ptr;


		static Standard_Integer NbSurfaces(const TopoDS_Shape& theShape);

		static face_ptr GetSurface
		(
			const TopoDS_Face& theFace
		);

		static faceList GetSurfaces
		(
			const TopoDS_Shape& theShape
		);

		static edgeList RetrieveEdges
		(
			const faceList& theFaces
		);

		static edgeList RetrieveNonDegeneratedEdges
		(
			const faceList& theFaces
		);

		static triangulation3d_ptr GetTriangulation
		(
			const TopoDS_Face& theFace
		);

		static triangulation3dList GetTriangulation
		(
			const TopoDS_Shape& theShape
		);

		static std::shared_ptr<shellList> TrackShells
		(
			const faceList& theFaces
		);

		//- Warning: This function is on the early stage!
		static Standard_Boolean InnerHoles
		(
			const shellList& theShells,
			shellList& theInners,
			shell_ptr& theOuters
		);

		static void GetVertices
		(
			const TopoDS_Edge& theEdge,
			TopoDS_Vertex& Vtx0,
			TopoDS_Vertex& Vtx1
		);

		static void MatchEdges
		(
			const solid_ptr& theSolid,
			solid_ptr& modified
		);

		static TopoDS_Shape RepairWithIGES(const TopoDS_Shape & theShape);

		static void ExportToPlt(const TopoDS_Shape& theShape, OFstream& File);

		static void ExportToIGES(const TopoDS_Shape& theShape, const word& FileName);

		static void Triangulation(const TopoDS_Shape& theShape, const Standard_Real theDeflection = 0.1, const Standard_Real theAngle = 1.0);
	};
}

#endif // !_Cad3d_SolidTools_Header
