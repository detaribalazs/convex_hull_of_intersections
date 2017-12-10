#pragma once

#include <Shapes.h>

#include <array>
#include <cassert>
#include <ostream>

namespace gk
{
    class Intersections
    {
        using array_type = std::array<Point, 2>;

        public:
            using iterator = array_type::iterator;
            using const_iterator = array_type::const_iterator;

            Intersections() = default;

            Intersections(const Point& p1)
                : points{p1}, count(1)
            {}

            Intersections(const Point& p1, const Point& p2)
                : points{p1, p2}, count(2)
            {}

            void add(const Point& p);

            void clear() { count = 0; }

            iterator erase(const_iterator it);

            const Point& operator[] (unsigned i) const;

            bool empty() const { return count == 0; }

            unsigned size() const { return count; }

            auto begin() const { return points.begin(); }
            auto begin()       { return points.begin(); }
            auto end() const { return points.begin() + count; }
            auto end()       { return points.begin() + count; }

            bool operator== (const Intersections& that) const;
            bool operator!= (const Intersections& that) const;

        private:
            std::array<Point, 2> points;
            unsigned count = 0;
    };

    std::ostream& operator<< (std::ostream& out, const Intersections& intersections);


    Intersections intersect(const Line& l1, const Line& l2);
    Intersections intersect(const Line& l, const Circle& circle);

    Intersections intersect(const LineSegment& l1, const LineSegment& l2);
    Intersections intersect(const LineSegment& l1, const Circle& c2);
    Intersections intersect(const Circle& c1, const Circle& c2);
    Intersections intersect(const Circle& c1, const LineSegment& l2);
}
