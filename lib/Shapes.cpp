#include <Shapes.h>

#include <cassert>
#include <cmath>

using namespace gk;

// =================================================================================================
bool Point::operator< (const Point& p) const
{
    return x < p.x ? true : (p.x < x ? false : y < p.y);
}

// =================================================================================================
Point& Point::operator+= (const Vector& p)
{
    x += p.x;
    y += p.y;
    return *this;
}

// =================================================================================================
Point Point::operator+ (const Vector& p) const
{
    return Point{x + p.x, y + p.y};
}

// =================================================================================================
Point& Point::operator-= (const Vector& p)
{
    x -= p.x;
    y -= p.y;
    return *this;
}

// =================================================================================================
Point Point::operator- (const Vector& p) const
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
Line Line::operator+ (const Vector& p) const
{
    return Line{a, b, c + a*p.x + b*p.y};
}

// =================================================================================================
Line Line::operator- (const Vector& p) const
{
    return Line{a, b, c - a*p.x - b*p.y};
}

// =================================================================================================
bool Line::operator==(const Line& l) const
{
    if (a == 0.0 && l.a == 0.0)
        return b / l.b == c / l.c;
    if (b == 0.0 && l.b == 0.0)
        return a / l.a == c / l.c;
    if (c == 0.0 && l.c == 0.0)
        return a / l.a == b / l.b;
    return a / l.a == b / l.b && a / l.a == c / l.c;
}

// =================================================================================================
std::ostream& gk::operator<<(std::ostream& out, const Line& l)
{
    return out << "Line("<< l.a << ", " << l.b << ", " << l.c << ')';
}

// =================================================================================================
bool Line::valid(const Point& p) const
{
    return std::fabs(a*p.x+b*p.y - c) < 1e-5;
}

// =================================================================================================
Line::Line(float a, float b, float c)
    : a(a), b(b), c(c)
{
    assert(a != 0.0 || b != 0.0 || c != 0.0);
}

// =================================================================================================
Line::Line(const Point& p1, const Point& p2)
{
    assert (p1 != p2);

    const auto delta_x = p2.x - p1.x;
    const auto delta_y = p2.y - p1.y;

    if (std::fabs(delta_x) > std::fabs(delta_y))
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
LineSegment LineSegment::operator+ (const Vector& p) const
{
    return LineSegment(_bounds + p, _line + p);
}

// =================================================================================================
LineSegment LineSegment::operator- (const Vector& p) const
{
    return LineSegment(_bounds - p, _line - p);
}

// =================================================================================================
LineSegment::LineSegment(const Point& p1, const Point& p2)
    : _bounds(p1, p2)
    , _line(p1, p2)
//    , _line(std::min(p1, p2), std::max(p1, p2))
{}

// =================================================================================================
LineSegment::LineSegment(const BoundsXY& bounds, const Line& line)
    : _bounds(bounds), _line(line)
{}

// =================================================================================================
bool LineSegment::valid(const Point& p) const
{
    return _bounds.valid(p) && _line.valid(p);
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
