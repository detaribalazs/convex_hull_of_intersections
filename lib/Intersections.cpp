#include <Intersections.h>

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
Intersections gk::intersect(const LineSegment&, const Circle&)
{
    return {};
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
