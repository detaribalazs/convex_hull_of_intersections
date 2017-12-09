#include <Shapes.h>

#include <cmath>

using namespace gk;

// =================================================================================================
std::ostream& gk::operator<<(std::ostream& out, const Point& p)
{
    return out << p.x << ", " << p.y;
}

// =================================================================================================
inline float square(float x)
{
    return x*x;
}

// =================================================================================================
float gk::distance(const Point& p1, const Point& p2)
{
    return sqrt(square(p1.x-p2.x) + square(p1.y-p2.y));
}

// =================================================================================================
float LineSegment::get_y(float x) const
{
    return endPoints[0].y + slope() * (x - endPoints[0].x);
}

// =================================================================================================
bool LineSegment::valid_x(float x) const
{
    return std::min(endPoints[0].x, endPoints[1].x) <= x
        && std::max(endPoints[0].x, endPoints[1].x) >= x;
}

// =================================================================================================
bool LineSegment::valid_y(float y) const
{
    return std::min(endPoints[0].y, endPoints[1].y) <= y
        && std::max(endPoints[0].y, endPoints[1].y) >= y;
}
