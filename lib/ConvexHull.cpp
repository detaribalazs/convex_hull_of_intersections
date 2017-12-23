#include <ConvexHull.h>
#include <ConvexHullHelpers.h>

#include <algorithm>

using namespace gk;

// =================================================================================================
std::vector<Point> gk::convex_hull(std::vector<Point> points)
{
    using namespace ::gk::detail;

    if (points.size() < 3)
        return {};

    auto minp = std::min_element(points.begin(), points.end(), CompareYX());

	// put the point with the lowest y coordinate to the front
    std::iter_swap(minp, points.begin());

	// sort the rest of the points by angle between x axis and the line from points[0] to the point
	std::sort(points.begin() + 1, points.end(), CompareAngle{points[0]});

    // start with a hull of the first 3 points
    auto point = points.begin() + 3;
    std::vector<Point> hull(points.begin(), point);

    while (point != points.end())
    {
        while (hull.size() > 1 &&
                counter_clockwise(*std::next(hull.rbegin()), hull.back(), *point) <= 0)
        {
            hull.pop_back();
        }

        hull.push_back(*point);
        ++point;
    }

    if (hull.size() >= 3 &&
            counter_clockwise(*std::next(hull.rbegin()), hull.back(), hull.front()) == 0)
    {
        // the last point is on the line from the last but one point  and the first point
        hull.pop_back();
    }

    if (hull.size() < 3 || counter_clockwise(hull[0], hull[1], hull[2]) == 0)
        hull.clear();

    return hull;
}
