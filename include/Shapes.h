#pragma once

#include <ostream>

namespace gk
{
    struct Point;
    using Vector = Point;

    struct Point
    {
        float x, y;

        // comparison operators
        bool operator== (const Point& p) const { return x == p.x && y == p.y; }
        bool operator!= (const Point& p) const { return x != p.x || y != p.y; }
        bool operator< (const Point& p) const;

        // translations by a vector
        Point& operator+= (const Vector& p);
        Point& operator-= (const Vector& p);
        Point operator+ (const Vector& p) const;
        Point operator- (const Vector& p) const;
    };

    float distance(const Point& p1, const Point& p2);

    std::ostream& operator<<(std::ostream& out, const Point& p);

    struct Line
    {
        // coefficients of the line equation: ax + by = c
        float a, b, c;

        Line() {}

        // construct from coefficients
        Line(float a, float b, float c);

        // construct from two points on the line
        Line(const Point& p1, const Point& p2);

        float slope_x() const
        { return -b / a; }

        float slope_y() const
        { return -a / b; }

        float get_x(float y) const
        { return (c - b*y) / a; }

        float get_y(float x) const
        { return (c - a*x) / b; }

        // translate by a vector
        Line operator+ (const Vector& p) const;
        Line operator- (const Vector& p) const;

        bool operator==(const Line& l) const;

        bool valid(const Point& p) const;
    };

    std::ostream& operator<<(std::ostream& out, const Line& l);

    struct Bounds
    {
        float lower, upper;

        Bounds operator+ (float d) const
        { return {lower + d, upper + d}; }

        Bounds operator- (float d) const
        { return {lower - d, upper - d}; }

        bool valid(float value) const
        { return lower <= value && value <= upper; }
    };

    struct BoundsXY
    {
        Bounds x, y;

        // construct from two corners of a rectangle
        BoundsXY(const Point& p1, const Point& p2)
            : x{std::min(p1.x, p2.x), std::max(p1.x, p2.x)}
            , y{std::min(p1.y, p2.y), std::max(p1.y, p2.y)}
        {}

        // construct from separate x and y bounds
        BoundsXY(const Bounds& x, const Bounds& y)
            : x(x), y(y)
        {}

        // translations
        BoundsXY operator+ (const Vector& p) const
        { return {x + p.x, y + p.y}; }
        BoundsXY operator- (const Vector& p) const
        { return {x - p.x, y - p.y}; }

        bool valid(const Point& p) const
        { return x.valid(p.x) && y.valid(p.y); }
    };

    class LineSegment
    {
        public:
            // construct from two points
            LineSegment(const Point& p1, const Point& p2);

            // construct from bounds and an infinite line
            LineSegment(const BoundsXY& bounds, const Line& line);

            // translations
            LineSegment operator+ (const Vector& p) const;
            LineSegment operator- (const Vector& p) const;

            // bounds checking
            bool valid(const Point& p) const;

            const Line& line() const { return _line; }

        private:
            BoundsXY _bounds;
            Line _line;
    };

    struct Circle
    {
        Point center;
        float radius;

        bool operator == (const Circle& c) const
        { return center == c.center && radius == c.radius; }

        // is point inside the circle
        bool is_inside(const Point& p) const;

        // is point on the circle
        bool valid(const Point& p) const;
    };
}
