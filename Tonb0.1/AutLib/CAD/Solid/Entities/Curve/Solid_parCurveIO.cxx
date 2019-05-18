#include <Solid_parCurve.hxx>

#include <error.hxx>
#include <OSstream.hxx>
#include <TecPlot_Opencascade.hxx>

//void AutLib::Solid_parCurve::ExportToPlt(OFstream & File) const
//{
//	if (theCurve_.IsNull())
//	{
//		FatalErrorIn("void AutLib::Solid_Curve::ExportToPlt(OFstream & File) const")
//			<< "Null curve encountered!"
//			<< abort(FatalError);
//	}
//
//	Io::ExportCurve
//	(
//		*theCurve_,
//		FirstParameter(),
//		LastParameter(),
//		NB_OF_DIVISION,
//		File
//	);
//}