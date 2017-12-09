#include <Intersections.h>

#include <cmath>
#include <iterator>
#include <limits>

using namespace gk;

// =================================================================================================
std::ostream& gk::operator<< (std::ostream& out, const Intersections& intersections)
{
    out << "Intersections( ";
    std::copy(intersections.begin(), intersections.end(), std::ostream_iterator<Point>(out, " "));
    out << ')';
    return out;
}

// =================================================================================================
bool Intersections::operator== (const Intersections& that) const
{
    if (count != that.count)
        return false;

    switch (count)
    {
        case 2:
            if (points[1] != that.points[1])
                return false;
            // [[fallthrough]]
        case 1:
            if (points[0] != that.points[0])
                return false;
    }
    return true;
}

// =================================================================================================
static Intersections intersectVertical(const LineSegment& l1, const LineSegment& l2)
{
    assert(l1[0].x == l1[1].x);

    if (!l2.valid_x(l1[0].x))
        return {};
    auto y = l2.get_y(l1[0].x);
    if (!l1.valid_y(y))
        return {};
    return Point{l1[0].x, y};
}

// =================================================================================================
Intersections gk::intersect(const LineSegment& l1, const LineSegment& l2)
{
    if (l1.slope() == l2.slope())
        return {};

    if (l1.is_vertical())
    {
        if (l2.is_vertical())
            return {};
        return intersectVertical(l1, l2);
    }

    if (l2.is_vertical())
        return intersectVertical(l2, l1);

    const auto ix = (l1[0].y - l2[0].y) / (l2.slope() - l1.slope());
    if (!l1.valid_x(ix) || !l2.valid_x(ix))
        return {};

    return Point{ix, l1.get_y(ix)};
}

// =================================================================================================
inline float square(float x)
{
    return x*x;
}

// =================================================================================================
static Intersections intersectVertical(const LineSegment& l, const Circle& c)
{
    assert(l[0].x == l[1].x);

    if (std::fabs(c.center.x - l[0].x) > c.radius)
        return {};

    const auto ry = std::sqrt(square(c.radius) - square(c.center.x - l[0].x));

    if (ry < 1e-4)
    {
        if (l.valid_y(c.center.y))
            return Point{l[0].x, c.center.y};
        return {};
    }

    Intersections isec;

    if (l.valid_y(c.center.y - ry))
        isec.add(Point{l[0].x, c.center.y - ry});
    if (l.valid_y(c.center.y + ry))
        isec.add(Point{l[0].x, c.center.y + ry});

    return isec;
}

// =================================================================================================
Intersections gk::intersect(const LineSegment& l, const Circle& circle)
{
    // both end-points inside the circle
    if (circle.is_inside(l[0]) && circle.is_inside(l[1]))
        return {};

    if (l.is_vertical())
        return intersectVertical(l, circle);

    const auto m = l.slope();
    const auto y1 = l.get_y(0.0);
    const auto a = square(m) + 1;
    const auto b = 2 * y1 * m;
    const auto c = square(y1) - square(circle.radius);
    const auto srbsmfac = sqrt(square(b) - 4 * a * c);
    const float x1 = (-b + srbsmfac) / (2 * a);
    const float x2 = (-b - srbsmfac) / (2 * a);

    Intersections isec;

    if (l.valid_x(x1))
        isec.add(Point{x1, l.get_y(x1)});

    if (l.valid_x(x2) && std::fabs(x2 - x1) > 1e-4)
        isec.add(Point{x2, l.get_y(x2)});

    return isec;
}

// =================================================================================================
Intersections gk::intersect(const Circle&, const Circle&)
{
    return {};
}

// =================================================================================================
Intersections gk::intersect(const Circle& c1, const LineSegment& l2)
{
    return intersect(l2, c1);
}
