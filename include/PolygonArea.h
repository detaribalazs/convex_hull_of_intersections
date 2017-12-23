#pragma once

#include <Shapes.h>

#include <vector>

namespace gk
{
    // returns the area of the convex polygon
    float convex_area(std::vector<Point> points);
}
