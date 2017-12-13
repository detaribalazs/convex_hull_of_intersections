#include <ConvexHull.h>
#include <PolygonArea.h>
#include <ShapeStorage.h>

#include "unit_test.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <chrono>
#include <random>

using namespace gk;
using namespace std::chrono_literals;

// =================================================================================================
namespace
{
    class Stopper
    {
        using time_point = std::chrono::high_resolution_clock::time_point;

        public:
            Stopper(std::string tcName, std::string name = std::string())
                : tcName(std::move(tcName)), name(std::move(name))
                , start(std::chrono::high_resolution_clock::now())
            {}

            ~Stopper()
            {
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed_time = end - start;

                std::cout << tcName;
                if (!name.empty())
                    std::cout << '/' << name;

                std::cout << ": "
                    << std::fixed << std::setprecision(12) << elapsed_time.count() << " sec" << std::endl;

                CHECK(elapsed_time < 3.0s);
            }

        private:
            std::string tcName, name;
            time_point start;
    };

    class Randomized
    {
        public:
            Randomized()
                : gen(rd()), dis(-10.0f, 10.0f)
            {}

        protected:
            float rnd() const
            { return dis(gen); }

        private:
            static std::random_device rd;
            mutable std::mt19937 gen;
            mutable std::uniform_real_distribution<float> dis;
    };

    std::random_device Randomized::rd;

    class RandomPoints
        : public std::iterator<std::input_iterator_tag, Point>
        , private Randomized
    {
        public:
            Point operator* ()            { return {rnd(), rnd()}; }
            RandomPoints& operator++()    { return *this; }
            RandomPoints& operator++(int) { return *this; }
    };

    class RandomLines
        : public std::iterator<std::input_iterator_tag, LineSegment>
        , private Randomized
    {
        public:
            LineSegment operator* ()      { return LineSegment{{rnd(), rnd()}, {rnd(), rnd()}}; }
            RandomLines& operator++()    { return *this; }
            RandomLines& operator++(int) { return *this; }
    };

    class RandomCircles
        : public std::iterator<std::input_iterator_tag, Circle>
        , private Randomized
    {
        public:
            Circle operator* ()      { return Circle{{rnd(), rnd()}, rnd()}; }
            RandomCircles& operator++()    { return *this; }
            RandomCircles& operator++(int) { return *this; }
    };

    // NOTE: available in C++17
    template<class InputIt, class Size, class UnaryFunction>
    InputIt for_each_n(InputIt first, Size n, UnaryFunction f)
    {
        for (Size i = 0; i < n; ++first, (void) ++i) {
            f(*first);
        }
        return first;
    }
}

#define TIMED_BLOCK(block_name) Stopper block_name(this->name, #block_name)

// =================================================================================================
TEST_CASE(performance_Intersections)
{
    {
        ShapeStorage shapes;
        for_each_n(RandomCircles(), 1000, [&] (Circle&& c)      { shapes.add(std::move(c)); });
        size_t pcount = 0;

        std::cout << "random circles: " << shapes.size() << std::endl;
        {
            TIMED_BLOCK(one_thousand_circles);
            pcount = shapes.intersectAll().size();
        }
        std::cout << "intersection points: " << pcount << std::endl;
    }

    {
        ShapeStorage shapes;
        for_each_n(RandomLines(),   1000, [&] (LineSegment&& l) { shapes.add(std::move(l)); });
        size_t pcount = 0;

        std::cout << "random lines: " << shapes.size() << std::endl;
        {
            TIMED_BLOCK(one_thousand_lines);
            pcount = shapes.intersectAll().size();
        }
        std::cout << "intersection points: " << pcount << std::endl;
    }

    {
        ShapeStorage shapes;
        for_each_n(RandomCircles(), 1000, [&] (Circle&& c)      { shapes.add(std::move(c)); });
        for_each_n(RandomLines(),   1000, [&] (LineSegment&& l) { shapes.add(std::move(l)); });
        size_t pcount = 0;

        std::cout << "random lines and circles: " << shapes.size() << std::endl;
        {
            TIMED_BLOCK(two_thousand_shapes);
            pcount = shapes.intersectAll().size();
        }
        std::cout << "intersection points: " << pcount << std::endl;
    }

    {
        ShapeStorage shapes;
        for_each_n(RandomCircles(), 1500, [&] (Circle&& c)      { shapes.add(std::move(c)); });
        for_each_n(RandomLines(),   1500, [&] (LineSegment&& l) { shapes.add(std::move(l)); });
        size_t pcount = 0;

        std::cout << "random lines and circles: " << shapes.size() << std::endl;
        {
            TIMED_BLOCK(three_thousand_shapes);
            pcount = shapes.intersectAll().size();
        }
        std::cout << "intersection points: " << pcount << std::endl;
    }
}

// =================================================================================================
TEST_CASE(performance_ConvexHull)
{
    std::vector<Point> points;
    size_t pcount = 0;

    points.resize(1000);
    std::copy_n(RandomPoints(), points.size(), points.begin());
    std::cout << "random points: " << points.size() << std::endl;
    {
        TIMED_BLOCK(one_thousand_points);
        pcount = convexHull(points).size();
    }
    std::cout << "points on convex hull: " << pcount << std::endl;

    points.resize(10000);
    std::copy_n(RandomPoints(), points.size(), points.begin());
    std::cout << "random points: " << points.size() << std::endl;
    {
        TIMED_BLOCK(ten_thousand_points);
        pcount = convexHull(points).size();
    }
    std::cout << "points on convex hull: " << pcount << std::endl;

    points.resize(100000);
    std::copy_n(RandomPoints(), points.size(), points.begin());
    std::cout << "random points: " << points.size() << std::endl;
    {
        TIMED_BLOCK(hundred_thousand_points);
        pcount = convexHull(points).size();
    }
    std::cout << "points on convex hull: " << pcount << std::endl;
}

// =================================================================================================
TEST_CASE(performance_PolygonArea)
{
    std::vector<Point> points;
    float parea;

    points.resize(1000);
    std::copy_n(RandomPoints(), points.size(), points.begin());
    std::cout << "random points: " << points.size() << std::endl;
    {
        TIMED_BLOCK(one_thousand_points);
        parea = area(points);
    }
    std::cout << "area: " << parea << std::endl;

    points.resize(10000);
    std::copy_n(RandomPoints(), points.size(), points.begin());
    std::cout << "random points: " << points.size() << std::endl;
    {
        TIMED_BLOCK(ten_thousand_points);
        parea = area(points);
    }
    std::cout << "area: " << parea << std::endl;

    points.resize(100000);
    std::copy_n(RandomPoints(), points.size(), points.begin());
    std::cout << "random points: " << points.size() << std::endl;
    {
        TIMED_BLOCK(hundred_thousand_points);
        parea = area(points);
    }
    std::cout << "area: " << parea << std::endl;
}
