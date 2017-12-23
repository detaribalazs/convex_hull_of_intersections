#include <ConvexHull.h>
#include <ConvexHullHelpers.h>

#include "unit_test.h"

#include <algorithm>
#include <iterator>

using namespace gk;
using namespace gk::detail;

// =================================================================================================
TEST_CASE(convex_hull_details_counter_clockwise)
{
    CHECK(counter_clockwise(Vector{1, 2}, Vector{2, 4}, Vector{4, 8}) == 0);
    CHECK(counter_clockwise(Vector{1, 2}, Vector{2, 3}, Vector{4, 8}) > 0);
    CHECK(counter_clockwise(Vector{1, 2}, Vector{2, 5}, Vector{4, 8}) < 0);
}

// =================================================================================================
TEST_CASE(convex_hull_CompareYX)
{
    std::vector<Point> points{
        {-1,-1}, {10,0}, {0,10}, {1,1}, {0,1,}, {1,0}, {2,2}, {2,1}, {1,2},
        {3,2}, {2,3}, {3,1}, {1,3}, {5,4}, {5,5}, {4,5}, {1,10}};

    std::sort(points.begin(), points.end(), CompareYX());
    std::copy(points.begin(), points.end(), std::ostream_iterator<Point>(std::cout, "\n"));
    CHECK_EQ(points[0], (Point{-1,-1}));
    CHECK_EQ(points[1], (Point{1,0}));
    CHECK_EQ(points[2], (Point{10,0}));
    CHECK_EQ(points.back(), (Point{1,10}));
}

// =================================================================================================
TEST_CASE(convex_hull_CompareAngle)
{
    std::vector<Point> points{
        {-1,-1}, {10,0}, {0,10}, {1,1}, {0,1,}, {1,0}, {2,2}, {2,1}, {1,2},
        {3,2}, {2,3}, {3,1}, {1,3}, {5,4}, {5,5}, {4,5}, {1,10}};

    std::sort(points.begin() + 1, points.end(), CompareAngle{points[0]});

    CHECK_EQ(points[0], (Point{-1,-1}));
    CHECK_EQ(points[1], (Point{10, 0}));
    CHECK_EQ(points[2], (Point{1,  0}));
    CHECK_EQ(points[3], (Point{3,  1}));
    CHECK_EQ(points.back(), (Point{0, 10}));
}

// =================================================================================================
TEST_CASE(convex_hull_all_colinear)
{
    std::vector<Point> points{{-3,-3}, {-1,-1}, {0,0}, {1,1}, {5,5}};

    auto hull = convex_hull(points);
    CHECK_EQ(hull.size(), 0);
    points.pop_back();
    CHECK_EQ(hull.size(), 0);
    points.pop_back();
    CHECK_EQ(hull.size(), 0);
    points.pop_back();
    CHECK_EQ(hull.size(), 0);
    points.pop_back();
    CHECK_EQ(hull.size(), 0);
}

// =================================================================================================
TEST_CASE(convex_hull_triangle)
{
    std::vector<Point> points{
        {-1,-1}, {10,0}, {0,10}, //< this is the convex hull
        {1,1}, {0,1}, {1,0}, {2,2}, {2,1}, {1,2}, {3,0},
        {3,2}, {2,3}, {3,1}, {1,3}, {5,4}, {5,5}, {4,5}
    };

    auto hull = convex_hull(points);
    std::copy(hull.begin(), hull.end(), std::ostream_iterator<Point>(std::cout, "\n"));
    CHECK_EQ(hull.size(), 3);
    CHECK_EQ(hull[0], (Point{-1,-1}));
    CHECK_EQ(std::min(hull[1], hull[2]), (Point{0, 10}));
    CHECK_EQ(std::max(hull[1], hull[2]), (Point{10, 0}));
}

// =================================================================================================
TEST_CASE(convex_hull_triangle_with_colinear_edges)
{
    std::vector<Point> points{
        {0,0}, {10,0}, {0,10}, //< this is the convex hull
        {1,1}, {0,1,}, {1,0}, {2,2}, {2,1}, {1,2},
        {3,2}, {2,3}, {3,1}, {1,3}, {5,4}, {5,5}, {4,5}
    };

    auto hull = convex_hull(points);
    std::copy(hull.begin(), hull.end(), std::ostream_iterator<Point>(std::cout, "\n"));
    CHECK_EQ(hull.size(), 3);
    CHECK_EQ(hull[0], (Point{0, 0}));
    CHECK_EQ(hull[1], (Point{10, 0}));
    CHECK_EQ(hull[2], (Point{0, 10}));
}

// =================================================================================================
TEST_CASE(convex_hull_rectangle)
{
    std::vector<Point> points{
        {-1.0,-1.0}, { 1.0, 1.0}, { 1.0,-1.0}, {-1.0, 1.0}, //< this is the convex hull
        { 0.3, 0.6}, { 0.9,-0.8}, {-0.9, 0.3}, { 0.0, 0.1},
        {-0.3,-0.6}, {-0.9, 0.8}, { 0.9,-0.3}, { 0.0,-0.1}
    };

    auto hull = convex_hull(points);
    std::copy(hull.begin(), hull.end(), std::ostream_iterator<Point>(std::cout, "\n"));
    CHECK_EQ(hull.size(), 4);
    CHECK_EQ(*std::min_element(hull.begin(), hull.end()), (Point{-1,-1}));
    CHECK_EQ(*std::max_element(hull.begin(), hull.end()), (Point{ 1, 1}));
    CHECK(std::find(hull.begin(), hull.end(), Point{-1, 1}) != hull.end());
    CHECK(std::find(hull.begin(), hull.end(), Point{ 1,-1}) != hull.end());
}

// =================================================================================================
TEST_CASE(convex_hull_rectangle_with_colinear_edges)
{
    std::vector<Point> points{
        {-1.0,-1.0}, { 1.0, 1.0}, { 1.0,-1.0}, {-1.0, 1.0}, //< this is the convex hull
        { 0.3, 0.6}, { 0.9,-0.8}, {-0.9, 0.3}, { 0.0, 0.1},
        {-0.3,-0.6}, {-0.9, 0.8}, { 0.9,-0.3}, { 0.0,-0.1},
        { 0.3, 1  }, { 1  ,-0.8}, {-1  , 0.3}, { 0  , 1  },
        {-0.3,-1  }, {-1  , 0.8}, { 1  ,-0.3}, { 1  ,-0.1}
    };

    auto hull = convex_hull(points);
    std::copy(hull.begin(), hull.end(), std::ostream_iterator<Point>(std::cout, "\n"));
    CHECK_EQ(hull.size(), 4);
    CHECK_EQ(*std::min_element(hull.begin(), hull.end()), (Point{-1,-1}));
    CHECK_EQ(*std::max_element(hull.begin(), hull.end()), (Point{ 1, 1}));
    CHECK(std::find(hull.begin(), hull.end(), Point{-1, 1}) != hull.end());
    CHECK(std::find(hull.begin(), hull.end(), Point{ 1,-1}) != hull.end());
}

// =================================================================================================
TEST_CASE(convex_hull_example)
{
    std::vector<Point> points{
        { 1.3720, -4.8081},
        {-3.9105,  3.1158},
        { 3.0000,  9.0000},
        {10.0000,  2.0000},
        { 2.0496,  2.4463},
        { 5.4773,  3.6705},
        {-1.3000,  1.2500},
        { 3.9135,  3.1120},
        { 9.3064,  5.0380},
        { 4.9512, -0.6971},
        {-0.2994,  4.9910},
        { 7.4496, -3.4038},
        {-2.0311,  6.8670},
        { 6.6981,  7.9434},
        {-2.6519, -2.1298}
    };

    auto hull = convex_hull(points);
    std::copy(hull.begin(), hull.end(), std::ostream_iterator<Point>(std::cout, "\n"));
    CHECK_EQ(hull.size(), 9);

    std::sort(hull.begin(), hull.end());
    CHECK_EQ(hull[0], (Point{-3.9105,  3.1158}));
    CHECK_EQ(hull[1], (Point{-2.6519, -2.1298}));
    CHECK_EQ(hull[2], (Point{-2.0311,  6.8670}));
    CHECK_EQ(hull[3], (Point{ 1.3720, -4.8081}));
    CHECK_EQ(hull[4], (Point{ 3.0000,  9.0000}));
    CHECK_EQ(hull[5], (Point{ 6.6981,  7.9434}));
    CHECK_EQ(hull[6], (Point{ 7.4496, -3.4038}));
    CHECK_EQ(hull[7], (Point{ 9.3064,  5.0380}));
    CHECK_EQ(hull[8], (Point{10.0000,  2.0000}));
}
