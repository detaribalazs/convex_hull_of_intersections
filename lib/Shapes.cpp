#include <Shapes.h>

#include <cmath>

using namespace gk;

// =================================================================================================
bool Point::operator< (const Point& p) const
{
    return x < p.x ? true : (p.x < x ? false : y < p.y);
}

// =================================================================================================
Point& Point::operator+= (const Point& p)
{
    x += p.x;
    y += p.y;
    return *this;
}

// =================================================================================================
Point Point::operator+ (const Point& p) const
{
    return Point{x + p.x, y + p.y};
}

// =================================================================================================
Point& Point::operator-= (const Point& p)
{
    x -= p.x;
    y -= p.y;
    return *this;
}

// =================================================================================================
Point Point::operator- (const Point& p) const
{
    return Point{x - p.x, y - p.y};
}

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
Line Line::operator+ (const Point& p) const
{
    return Line{a, b, c + (std::fabs(b) < 1e-5 ? a*p.x : b*p.y)};
}

// =================================================================================================
Line Line::operator- (const Point& p) const
{
    return Line{a, b, c - (std::fabs(b) < 1e-5 ? a*p.x : b*p.y)};
}

// =================================================================================================
bool Line::valid(const Point& p) const
{
    return std::fabs(a*p.x+b*p.y - c) < 1e-5;
}

// =================================================================================================
Line::Line(const Point& p1, const Point& p2)
{
    const auto delta_x = p2.x - p1.x;
    const auto delta_y = p2.y - p1.y;

    if (delta_x > delta_y)
    {
        const auto y0 = p1.y - delta_y / delta_x * p1.x;
        a = - delta_y;
        b = delta_x;
        c = delta_x * y0;
    }
    else
    {
        const auto x0 = p1.x - delta_x / delta_y * p1.y;
        a = delta_y;
        b = - delta_x;
        c = delta_y * x0;
    }
}

// =================================================================================================
LineSegment LineSegment::operator+ (const Point& p) const
{
    return LineSegment(endPoints[0] + p, endPoints[1] + p);
}

// =================================================================================================
LineSegment LineSegment::operator- (const Point& p) const
{
    return LineSegment(endPoints[0] - p, endPoints[1] - p);
}

// =================================================================================================
LineSegment::LineSegment(const Point& p1, const Point& p2)
    : endPoints{std::min(p1, p2), std::max(p1, p2)}
    , _line(endPoints[0], endPoints[1])
{}

// =================================================================================================
float LineSegment::get_x(float y) const
{
    return endPoints[0].x + slope_x() * (y - endPoints[0].y);
}

// =================================================================================================
float LineSegment::get_y(float x) const
{
    return endPoints[0].y + slope_y() * (x - endPoints[0].x);
}

// =================================================================================================
bool LineSegment::valid_x(float x) const
{
    return (std::min(endPoints[0].x, endPoints[1].x) - x < 1e-5)
        && (std::max(endPoints[0].x, endPoints[1].x) - x > -1e-5);
}

// =================================================================================================
bool LineSegment::valid_y(float y) const
{
    return (std::min(endPoints[0].y, endPoints[1].y) - y < 1e-5)
        && (std::max(endPoints[0].y, endPoints[1].y) - y > -1e-5);
}

// =================================================================================================
bool LineSegment::valid(const Point& p) const
{
    return valid_x(p.x) && valid_y(p.y);
}

// =================================================================================================
bool Circle::is_inside(const Point& p) const
{
    return distance(center, p) < radius;
}

// =================================================================================================
bool Circle::valid(const Point& p) const
{
    return std::fabs(distance(center, p) - radius) < 1e-5;
}
