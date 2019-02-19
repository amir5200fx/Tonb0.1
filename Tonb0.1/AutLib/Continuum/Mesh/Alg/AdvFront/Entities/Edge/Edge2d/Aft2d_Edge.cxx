#include <Aft2d_Edge.hxx>

#ifdef USE_CGAL_PROCESSOR
#include <CGAL\Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL\Segment_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;

typedef Kernel::Segment_2 Segment;
typedef Kernel::Point_2 Point_2;
#endif

#ifdef USE_CGAL_PROCESSOR

Standard_Real AutLib::Aft2d_Edge::CalcDistance
(
	const Pnt2d & theCoord
) const
{
	Point_2 pt(theCoord.X(), theCoord.Y());

	const auto& P0 = Node0()->Coord();
	const auto& P1 = Node1()->Coord();

	Segment segment(Point_2(P0.X(), P0.Y()), Point_2(P1.X(), P1.Y()));
	return sqrt(CGAL::squared_distance(pt, segment));
}

Standard_Real AutLib::Aft2d_Edge::CalcSquareDistance
(
	const Pnt2d & theCoord
) const
{
	Point_2 pt(theCoord.X(), theCoord.Y());

	const auto& P0 = Node0()->Coord();
	const auto& P1 = Node1()->Coord();

	Segment segment(Point_2(P0.X(), P0.Y()), Point_2(P1.X(), P1.Y()));
	return CGAL::squared_distance(pt, segment);
}

Standard_Real AutLib::Aft2d_Edge::Oriented
(
	const Pnt2d & theCoord
) const
{
	Point_2 pt(theCoord.X(), theCoord.Y());

	const auto& P0 = Node0()->Coord();
	const auto& P1 = Node1()->Coord();

	return CGAL::area(pt, Point_2(P0.X(), P0.Y()), Point_2(P1.X(), P1.Y()));
}

#else

#endif