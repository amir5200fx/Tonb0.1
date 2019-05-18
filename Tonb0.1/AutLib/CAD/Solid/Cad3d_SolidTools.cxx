#include <Cad3d_SolidTools.hxx>

#include <Entity3d_Triangulation.hxx>
#include <Solid_Edge.hxx>
#include <Solid_Face.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopExp_Explorer.hxx>
#include <Bnd_Box.hxx>
#include <BRepBndLib.hxx>
#include <BRepMesh_FastDiscret.hxx>
#include <IGESControl_Controller.hxx>
#include <IGESControl_Writer.hxx>

AutLib::Cad3d_SolidTools::edgeList 
AutLib::Cad3d_SolidTools::RetrieveEdges
(
	const faceList & theFaces
)
{
	edgeList QEdges;
	for (const auto& x : theFaces)
	{
		Debug_Null_Pointer(x);
		const auto& face = *x;

		const auto edges = face.Edges();

		for (const auto& edge : edges)
		{
			/*if (edge->Face().lock())
			{
				QEdges.push_back(edge);
			}*/
			QEdges.push_back(edge);
		}
	}
	return std::move(QEdges);
}

AutLib::Cad3d_SolidTools::edgeList 
AutLib::Cad3d_SolidTools::RetrieveNonDegeneratedEdges
(
	const faceList & theFaces
)
{
	edgeList QEdges;
	for (const auto& x : theFaces)
	{
		Debug_Null_Pointer(x);
		const auto& face = *x;

		const auto edges = face.Edges();

		for (const auto& edge : edges)
		{
			/*if (edge->Face().lock())
			{
				QEdges.push_back(edge);
			}*/
			if (NOT edge->IsDegenerated())
				QEdges.push_back(edge);
		}
	}
	return std::move(QEdges);
}

AutLib::Cad3d_SolidTools::triangulation3d_ptr
AutLib::Cad3d_SolidTools::GetTriangulation
(
	const TopoDS_Face & theFace
)
{
	TopLoc_Location Loc;
	auto Triangulation = BRep_Tool::Triangulation(theFace, Loc);

	auto myTriangulation = std::make_shared<Entity3d_Triangulation>();
	if (Triangulation.IsNull()) return std::move(myTriangulation);

	const auto& triangles = Triangulation->Triangles();
	const auto& nodes = Triangulation->Nodes();

	auto& myTriangles = myTriangulation->Connectivity();
	auto& myPts = myTriangulation->Points();

	myTriangles.resize(triangles.Size());
	myPts.resize(nodes.Size());

	Standard_Integer K = 0;
	for (auto& x : myTriangles)
	{
		const auto& TriangleIndex = triangles.Value(K + triangles.Lower());

		Standard_Integer I1, I2, I3;
		TriangleIndex.Get(I1, I2, I3);

		x.Value(0) = I1;
		x.Value(1) = I2;
		x.Value(2) = I3;

		++K;
	}

	K = 0;
	for (auto& x : myPts)
	{
		x = Pnt3d(nodes.Value(K + nodes.Lower()));
		++K;
	}
	return std::move(myTriangulation);
}

AutLib::Cad3d_SolidTools::triangulation3dList 
AutLib::Cad3d_SolidTools::GetTriangulation
(
	const TopoDS_Shape & theShape
)
{
	triangulation3dList triList;
	for 
		(
			TopExp_Explorer Explorer(theShape, TopAbs_FACE);
			Explorer.More(); 
			Explorer.Next()
			)
	{
		triList.push_back(GetTriangulation(TopoDS::Face(Explorer.Current())));
	}

	return std::move(triList);
}

void AutLib::Cad3d_SolidTools::GetVertices
(
	const TopoDS_Edge & theEdge, 
	TopoDS_Vertex & Vtx0,
	TopoDS_Vertex & Vtx1
)
{
	TopExp_Explorer aVertexExp;
	aVertexExp.Init(theEdge.Oriented(TopAbs_FORWARD), TopAbs_VERTEX);

	if (aVertexExp.More())
	{
		Vtx0 = TopoDS::Vertex(aVertexExp.Current());
	}

	aVertexExp.Next();
	if (aVertexExp.More())
	{
		Vtx1 = TopoDS::Vertex(aVertexExp.Current());
	}
}

void AutLib::Cad3d_SolidTools::ExportToIGES
(
	const TopoDS_Shape & theShape,
	const word & FileName
)
{
	IGESControl_Controller::Init();

	IGESControl_Writer Writer("MM", 0);
	Writer.AddShape(theShape);
	Writer.ComputeModel();

	Standard_Boolean OK = Writer.Write(FileName.c_str());

	if (!OK)
	{
		FatalErrorIn("void ExportToIGES(const TopoDS_Shape& theShape, const word& FileName)")
			<< "Failed to write iges file" << endl
			<< abort(FatalError);
	}
}

void AutLib::Cad3d_SolidTools::Triangulation
(
	const TopoDS_Shape & theShape, 
	const Standard_Real theDeflection, 
	const Standard_Real theAngle
)
{
	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = theDeflection;
	Params.Angle = theAngle;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(theShape, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(theShape);
}