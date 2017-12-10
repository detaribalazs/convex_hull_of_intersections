#pragma once

#include <ostream>

namespace gk
{
    struct Point
    {
        float x, y;

        // comparison operators
        bool operator== (const Point& p) const { return x == p.x && y == p.y; }
        bool operator!= (const Point& p) const { return x != p.x || y != p.y; }
        bool operator< (const Point& p) const;

        // translations by a vector
        Point& operator+= (const Point& p);
        Point& operator-= (const Point& p);
        Point operator+ (const Point& p) const;
        Point operator- (const Point& p) const;
    };

    float distance(const Point& p1, const Point& p2);

    std::ostream& operator<<(std::ostream& out, const Point& p);

    struct Line
    {
        // coefficients of the line equation: ax + by = c
        float a, b, c;

        Line() {}

        // construct from coefficients
        Line(float a, float b, float c)
            : a(a), b(b), c(c)
        {}

        // construct from two points on the line
        Line(const Point& p1, const Point& p2);

        // translate by a vector
        Line operator+ (const Point& p) const;
        Line operator- (const Point& p) const;

        bool valid(const Point& p) const;
    };

    class LineSegment
    {
        public:
            LineSegment(const Point& p1, const Point& p2);

            // translations
            LineSegment operator+ (const Point& p) const;
            LineSegment operator- (const Point& p) const;

            // access end-points
            const Point& operator[](unsigned i) const { return endPoints[i]; }

            // line features
            float delta_y() const { return endPoints[1].y - endPoints[0].y;}
            float delta_x() const { return endPoints[1].x - endPoints[0].x; }

            float slope_y() const { return delta_y() / delta_x(); }
            float slope_x() const { return delta_x() / delta_y(); }

            bool is_vertical() const { return delta_x() == 0.0; }
            bool is_horizontal() const { return delta_y() == 0.0; }

            // evaluate the line equation (no bounds checking)
            float get_y(float x) const;
            float get_x(float y) const;

            // bounds checking
            bool valid_x(float x) const;
            bool valid_y(float y) const;
            bool valid(const Point& p) const;

            const Line& line() const
            { return _line; }

        private:
            Point endPoints[2];
            Line _line;
    };

    struct Circle
    {
        Point center;
        float radius;

        // is point inside the circle
        bool is_inside(const Point& p) const;

        // is point on the circle
        bool valid(const Point& p) const;
    };
}
