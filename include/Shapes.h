#pragma once

#include <ostream>

namespace gk
{
    struct Point
    {
        float x, y;

        bool operator== (const Point& p) const
        { return x == p.x && y == p.y; }

        bool operator!= (const Point& p) const
        { return x != p.x || y != p.y; }
    };

    float distance(const Point& p1, const Point& p2);

    std::ostream& operator<<(std::ostream& out, const Point& p);

    struct LineSegment
    {
        Point endPoints[2];

        LineSegment(const Point& p1, const Point& p2);

        const Point& operator[](unsigned i) const
        { return endPoints[i]; }

        float delta_y() const
        { return endPoints[1].y - endPoints[0].y;}

        float delta_x() const
        { return endPoints[1].x - endPoints[0].x; }

        float slope() const
        { return delta_y() / delta_x(); }

        bool is_vertical() const
        { return delta_x() == 0.0; }

        bool is_horizontal() const
        { return delta_x() == 0.0; }

        float get_y(float x) const;

        bool valid_x(float x) const;

        bool valid_y(float y) const;
    };

    struct Circle
    {
        Point center;
        float radius;

        bool is_inside(const Point& p) const
        {
            return distance(center, p) < radius;
        }
    };
}
