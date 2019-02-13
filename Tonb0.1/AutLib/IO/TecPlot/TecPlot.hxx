#pragma once
#ifndef _TecPlot_Header
#define _TecPlot_Header

#include <Standard_TypeDef.hxx>
#include <Stl_Vector.hxx>
#include <IOstream.hxx>
#include <OFstream.hxx>

namespace AutLib
{

	class Pnt3d;
	class Pnt2d;

	namespace Io
	{

		void WriteVariables
		(
			const word& theVariables,
			OFstream& theFile
		);

		void WriteFeTriangleZone
		(
			const Standard_Integer NbNodes,
			const Standard_Integer NbTriangles,
			OFstream& theFile
		);

		void WriteFeTetrahedralZone
		(
			const Standard_Integer NbNodes,
			const Standard_Integer NbTets,
			OFstream& theFile
		);

		void WriteCellCenteredFeTriangularZone
		(
			const Standard_Integer NbNodes,
			const Standard_Integer NbTris, 
			const Standard_Integer NbVar, 
			OFstream& theFile
		);

		void WriteCellCenteredFeTriangular3DZone
		(
			const Standard_Integer NbNodes,
			const Standard_Integer NbTris,
			const Standard_Integer NbVar,
			OFstream& theFile
		);

		void WriteCellCenteredFeTetrahedralZone
		(
			const Standard_Integer NbNodes,
			const Standard_Integer NbTets,
			const Standard_Integer NbVar, 
			OFstream& theFile
		);

		void WriteFeBrickZone
		(
			const Standard_Integer NbNodes,
			const Standard_Integer NbBricks, 
			OFstream& theFile
		);

		void WriteIorderedZone
		(
			const Standard_Integer NbNodes,
			OFstream& theFile
		);

		void ExportCurve
		(
			const Stl_Vector<Pnt3d>& Points,
			OFstream& File
		);

		void ExportCurve
		(
			const Stl_Vector<Pnt2d>& Points,
			OFstream& File
		);
	}
}

#endif // !_TecPlot_Header
