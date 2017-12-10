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
Intersections::iterator Intersections::erase(const_iterator it)
{
    switch (size())
    {
        case 2:
            if (it == begin())
            {
                std::iter_swap(begin(), begin() + 1);
                --count;
                return begin();
            }
            // [[fallthrough]]
        case 1:
            --count;
    }

    return end();
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
bool Intersections::operator!= (const Intersections& that) const
{
    return ! (*this == that);
}

// =================================================================================================
const Point& Intersections::operator[] (unsigned i) const
{
    assert(i < points.size());
    return points[i];
}

// =================================================================================================
void Intersections::add(const Point& p)
{
    assert(count < points.size());
    points[count++] = p;
}

// =================================================================================================
Intersections gk::intersect(const Line& l1, const Line& l2)
{
    const auto den = l1.a * l2.b - l2.a *l1.b;

    // the lines are parallel
    if (std::abs(den) < 1e-6)
        return {};

    return Point{(l1.c * l2.b - l2.c * l1.b) / den, (l1.a * l2.c - l2.a * l1.c) / den};
}

// =================================================================================================
Intersections gk::intersect(const LineSegment& l1, const LineSegment& l2)
{
    auto isec = intersect(l1.line(), l2.line());

    if (!isec.empty())
    {
        if (!l1.valid(isec[0]) || !l2.valid(isec[0]))
            isec.clear();
    }

    return isec;
}

// =================================================================================================
inline float square(float x)
{
    return x*x;
}

// =================================================================================================
Intersections gk::intersect(const Line& l, const Circle& circle)
{
    const auto lt = l - circle.center;
    const auto d = square(circle.radius) * (square(lt.a) + square(lt.b)) - square(lt.c);

    if (d < 0)
        return {};

    Intersections isec;

    const auto a2pb2 = square(lt.a) + square(lt.b);

    if (d < 1e-5)
    {
        Point p{lt.a * lt.c / a2pb2, lt.b * lt.c / a2pb2};
        p += circle.center;
        isec.add(p);
    }
    else
    {
        Point p1{
            float((lt.a * lt.c - lt.b * sqrt(d)) / a2pb2),
            float((lt.b * lt.c + lt.a * sqrt(d)) / a2pb2)};
        Point p2{
            float((lt.a * lt.c + lt.b * sqrt(d)) / a2pb2),
            float((lt.b * lt.c - lt.a * sqrt(d)) / a2pb2)};

        p1 += circle.center;
        p2 += circle.center;

        isec.add(p1);
        isec.add(p2);
    }

    return isec;
}

// =================================================================================================
Intersections gk::intersect(const LineSegment& ls, const Circle& circle)
{
    auto isec = intersect(ls.line(), circle);
    auto p = isec.begin();

    while (p != isec.end())
    {
        if (ls.valid(*p))
            ++p;
        else
            p = isec.erase(p);
    }

    return isec;
}

// =================================================================================================
Intersections gk::intersect(const Circle& c1, const Circle& c2)
{
    Line l{
        2 * (c2.center.x - c1.center.x),
        2 * (c2.center.y - c1.center.y),
        + square(c1.radius) - square(c1.center.x) - square(c1.center.y)
        - square(c2.radius) + square(c2.center.x) + square(c2.center.y)};
    return intersect(l, c1);
}

// =================================================================================================
Intersections gk::intersect(const Circle& c1, const LineSegment& l2)
{
    return intersect(l2, c1);
}
