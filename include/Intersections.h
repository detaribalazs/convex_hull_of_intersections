#pragma once

#include <Shapes.h>

#include <array>
#include <cassert>
#include <ostream>

namespace gk
{
    class Intersections
    {
        public:
            Intersections() = default;

            Intersections(const Point& p1)
                : points{p1}, count(1)
            {}

            Intersections(const Point& p1, const Point& p2)
                : points{p1, p2}, count(2)
            {}

            void add(const Point& p)
            {
                assert(count < points.size());
                points[count++] = p;
            }

            bool empty() const
            { return count == 0; }

            unsigned size() const
            { return count; }

            const Point& operator[] (unsigned i) const
            {
                assert(i < points.size());
                return points[i];
            }

            auto begin() const
            { return points.begin(); }

            auto end() const
            { return points.begin() + count; }

            bool operator== (const Intersections& that) const;

            bool operator!= (const Intersections& that) const
            { return ! (*this == that); }

        private:
            std::array<Point, 2> points;
            unsigned count = 0;
    };

    std::ostream& operator<< (std::ostream& out, const Intersections& intersections);


    Intersections intersect(const LineSegment& l1, const LineSegment& l2);
    Intersections intersect(const LineSegment& l1, const Circle& c2);
    Intersections intersect(const Circle& c1, const Circle& c2);
    Intersections intersect(const Circle& c1, const LineSegment& l2);
}
