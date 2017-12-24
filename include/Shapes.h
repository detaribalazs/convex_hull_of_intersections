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
        bool operator== (const Point& p) const noexcept
        { return x == p.x && y == p.y; }

        bool operator!= (const Point& p) const noexcept
        { return x != p.x || y != p.y; }

        bool operator< (const Point& p) const noexcept;

        // translations by a vector
        Point& operator+= (const Vector& p) noexcept;
        Point& operator-= (const Vector& p) noexcept;
        Point operator+ (const Vector& p) const noexcept;
        Point operator- (const Vector& p) const noexcept;
    };

    float distance(const Point& p1, const Point& p2) noexcept;

    std::ostream& operator<<(std::ostream& out, const Point& p);

    struct Line
    {
        // coefficients of the line equation: ax + by = c
        float a, b, c;

        // construct from coefficients
        Line(float a, float b, float c);

        // construct from two points on the line
        Line(const Point& p1, const Point& p2);

        float slope_x() const noexcept
        { return -b / a; }

        float slope_y() const noexcept
        { return -a / b; }

        float get_x(float y) const noexcept
        { return (c - b*y) / a; }

        float get_y(float x) const noexcept
        { return (c - a*x) / b; }

        // translate by a vector
        Line operator+ (const Vector& p) const noexcept;
        Line operator- (const Vector& p) const noexcept;

        bool operator==(const Line& l) const noexcept;

        bool valid(const Point& p) const noexcept;
    };

    std::ostream& operator<<(std::ostream& out, const Line& l);

    struct Bounds
    {
        float lower, upper;

        Bounds operator+ (float d) const noexcept
        { return {lower + d, upper + d}; }

        Bounds operator- (float d) const noexcept
        { return {lower - d, upper - d}; }

        bool valid(float value) const noexcept
        { return lower <= value && value <= upper; }
    };

    struct BoundsXY
    {
        Bounds x, y;

        // construct from two corners of a rectangle
        BoundsXY(const Point& p1, const Point& p2) noexcept
            : x{std::min(p1.x, p2.x), std::max(p1.x, p2.x)}
            , y{std::min(p1.y, p2.y), std::max(p1.y, p2.y)}
        {}

        // construct from separate x and y bounds
        BoundsXY(const Bounds& x, const Bounds& y) noexcept
            : x(x), y(y)
        {}

        // translations
        BoundsXY operator+ (const Vector& p) const noexcept
        { return {x + p.x, y + p.y}; }

        BoundsXY operator- (const Vector& p) const noexcept
        { return {x - p.x, y - p.y}; }

        bool valid(const Point& p) const noexcept
        { return x.valid(p.x) && y.valid(p.y); }
    };

    class LineSegment
    {
        public:
            // construct from two points
            LineSegment(const Point& p1, const Point& p2);

            // construct from bounds and an infinite line
            LineSegment(const BoundsXY& bounds, const Line& line) noexcept;

            // translations
            LineSegment operator+ (const Vector& p) const noexcept;
            LineSegment operator- (const Vector& p) const noexcept;

            // bounds checking
            bool valid(const Point& p) const noexcept;

            const Line& line() const  noexcept
            { return _line; }

        private:
            BoundsXY _bounds;
            Line _line;
    };

    struct Circle
    {
        Point center;
        float radius;

        bool operator == (const Circle& c) const noexcept
        { return center == c.center && radius == c.radius; }

        // is point inside the circle
        bool is_inside(const Point& p) const noexcept;

        // is point on the circle
        bool valid(const Point& p) const noexcept;
    };
}
