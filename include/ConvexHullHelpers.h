#pragma once

#include <Shapes.h>

#include <cmath>

namespace gk
{
    namespace detail
    {
        struct CompareAngle
        {
            Vector ref;

            // compare polar angles of lines from ref to a and from ref to b
            bool operator() (const Point& a, const Point& b) const noexcept
            {
                return atan2(a.y-ref.y, a.x-ref.x) < atan2(b.y-ref.y, b.x-ref.x);
            }
        };

        struct CompareYX
        {
            constexpr bool operator() (const Point& a, const Point& b) const noexcept
            {
                return a.y < b.y ? true : (b.y < a.y ? false : a.x < b.x);
            }
        };

        /*
         * Are p1, p2, p3 in a counter-clockwise turn?
         *   returns > 0 : counter-clockwise
         *   returns = 0 : colinear
         *   returns < 0 : clockwise
         */
        inline constexpr float counter_clockwise(const Point& p1, const Point& p2, const Point& p3) noexcept
        {
            return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
        }
    }
}
