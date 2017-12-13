#include <PolygonArea.h>

#include <algorithm>
#include <numeric>
#include <cmath>

using namespace gk;

// =================================================================================================
namespace
{
    class CollectSum
        : public std::iterator<
            std::output_iterator_tag,
            float, // value_type
            std::ptrdiff_t, // difference_type
            CollectSum*, // pointer
            CollectSum& > // reference
    {
        public:
            CollectSum(float& out)
                : out(out)
            {}

            CollectSum& operator* ()    { return *this; }
            CollectSum& operator++()    { return *this; }
            CollectSum& operator++(int) { return *this; }
            CollectSum& operator= (float value)
            {
                out += value;
                return *this;
            }

        private:
            float& out;
    };
}

// =================================================================================================
// length of a vector
static float length(const Vector& v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

// =================================================================================================
// dot product
static float dot(const Vector& a, const Vector& b)
{
    return a.x * b.x + a.y * b.y;
}

// =================================================================================================
// cosine of the angle between a and b
static float cosine(const Vector& a, const Vector& b)
{
    return dot(a, b) / length(a) / length(b);
}

// =================================================================================================
static float sine(const Vector& a, const Vector& b)
{
    auto cosAB = cosine(a, b);
    return sqrt(1 - cosAB*cosAB);
}

// =================================================================================================
static float triangleArea(const Point& a, const Point& b)
{
    // the 3rd point of the triangle is always the origo
    float da = length(a), db = length(b);
    return 0.5f * da * db * sine(a, b);
}

// =================================================================================================
static Point centroid(const std::vector<Point>& points)
{
    Point c = std::accumulate(points.begin(), points.end(), Point{0,0});
    c.x /= points.size();
    c.y /= points.size();
    return c;
}

// =================================================================================================
float gk::area(std::vector<Point> points)
{
    if (points.size() < 3)
        return 0.0f;

    // get the center of the point set
    auto c = centroid(points);
    // translate the polygon to be centered at the origo
    std::transform(points.begin(), points.end(), points.begin(),
            [c] (const Point& p) { return p - c; });
    // form a closed polygon
    points.push_back(points.front());

    float area = 0.0f;
    // sum the area of each trianlge formed by an edge and the origo
    // NOTE: C++17 transform_reduce could be used instead and CollectSum could be eliminated
    std::transform(
            points.begin(), points.end() - 1, // adjacent points of the polygon
            points.begin() + 1,
            CollectSum(area), // output
            triangleArea);

    return area;
}
