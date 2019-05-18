#include <Mesh_Curve.hxx>

namespace AutLib
{
	const Standard_Real Mesh_CurveInfo::DEFAULT_UNDER_RELAXATION(0.9);
	const Standard_Real Mesh_CurveInfo::DEFAULT_INTG_TOLERANCE(1.0E-10);
	const Standard_Integer Mesh_CurveInfo::DEFAULT_MAX_SUBDIVIDE_CURVE(10);

	const Standard_Real Mesh_CurveInfo::DEFAULT_CORRECT_TOLERANCE(0.05);
	const Standard_Integer Mesh_CurveInfo::DEFAULT_NB_CORRECTIONS(5);
}