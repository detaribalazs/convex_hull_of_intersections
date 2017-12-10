#include <Intersections.h>
#include "unit_test.h"

using namespace gk;

// =================================================================================================
TEST_CASE(intersect_circles_inside_each_other_no_intersection)
{
    Circle c1{Point{0,0}, 2}, c2{Point{0,0}, 3};

    CHECK_EQ(intersect(c1, c2), Intersections{});
}

// =================================================================================================
TEST_CASE(intersect_circles_inside_each_other_shifted_no_intersection)
{
    Circle c1{Point{0.3, 0.6}, 2}, c2{Point{-0.3, 0.2}, 3};

    CHECK_EQ(intersect(c1, c2), Intersections{});
}

// =================================================================================================
TEST_CASE(intersect_circles_outside_each_other_no_intersection)
{
    Circle c1{Point{1, 3}, 2}, c2{Point{5, 4}, 2};

    CHECK_EQ(intersect(c1, c2), Intersections{});
}

// =================================================================================================
IGNORE_TEST_CASE(intersect_circles_outside_each_other_two_intersections)
{
    Circle c1{Point{1, 3}, 2}, c2{Point{5, 4}, 3};

    auto isec = intersect(c1, c2);
    CHECK_EQ(isec.size(), 2);
    CHECK_EQ(isec[0], (Point{6.61851, 6.52595}));
    CHECK_EQ(isec[1], (Point{7.61678, 2.53288}));
    CHECK(c2.valid(isec[0]));
    CHECK(c2.valid(isec[1]));
    CHECK(c1.valid(isec[0]));
    CHECK(c1.valid(isec[1]));
}

// =================================================================================================
TEST_CASE(intersect_circles_inside_each_other_tangent)
{
    Circle c1{Point{1,1}, 2}, c2{Point{0,1}, 3};

    auto isec = intersect(c1, c2);
    CHECK_EQ(isec.size(), 1);
    CHECK_EQ(isec[0], (Point{3, 1}));
    CHECK(c1.valid(isec[0]));
    CHECK(c2.valid(isec[0]));
}

// =================================================================================================
TEST_CASE(intersect_circles_next_to_eachother_tangent)
{
    Circle c1{Point{0,0}, 2}, c2{Point{5,0}, 3};

    auto isec = intersect(c1, c2);
    CHECK_EQ(isec.size(), 1);
    CHECK_EQ(isec[0], (Point{2, 0}));
    CHECK(c1.valid(isec[0]));
    CHECK(c2.valid(isec[0]));
}

// =================================================================================================
TEST_CASE(intersect_circles_next_to_eachother_crossint)
{
    Circle c1{Point{0,0}, 3}, c2{Point{5,0}, 3};

    auto isec = intersect(c1, c2);
    CHECK_EQ(isec.size(), 2);
    CHECK_EQ(isec[0], (Point{2.5,  1.65831}));
    CHECK_EQ(isec[1], (Point{2.5, -1.65831}));
    CHECK(c1.valid(isec[0]));
    CHECK(c2.valid(isec[0]));
    CHECK(c1.valid(isec[1]));
    CHECK(c2.valid(isec[1]));
}

// =================================================================================================
TEST_CASE(intersect_circles_above_eachother_tangent)
{
    Circle c1{Point{3,1}, 2}, c2{Point{3,6}, 3};

    auto isec = intersect(c1, c2);
    CHECK_EQ(isec.size(), 1);
    CHECK_EQ(isec[0], (Point{3, 3}));
    CHECK(c1.valid(isec[0]));
    CHECK(c2.valid(isec[0]));
}

// =================================================================================================
TEST_CASE(intersect_circles_above_eachother_crossing)
{
    Circle c1{Point{3,1}, 3}, c2{Point{3,6}, 3};

    auto isec = intersect(c1, c2);
    CHECK_EQ(isec.size(), 2);
    CHECK_EQ(isec[0], (Point{1.34169, 3.5}));
    CHECK_EQ(isec[1], (Point{4.65831, 3.5}));
    CHECK(c1.valid(isec[0]));
    CHECK(c2.valid(isec[0]));
    CHECK(c1.valid(isec[1]));
    CHECK(c2.valid(isec[1]));
}

// =================================================================================================
TEST_CASE(intersect_circles_inside_each_other_crossing)
{
    Circle c1{Point{1,1}, 2}, c2{Point{-1,1}, 3};

    auto isec = intersect(c1, c2);
    CHECK_EQ(isec.size(), 2);
    CHECK_EQ(isec[0], (Point{1.25, -0.984313}));
    CHECK_EQ(isec[1], (Point{1.25,  2.98431}));
    CHECK(c1.valid(isec[0]));
    CHECK(c2.valid(isec[0]));
    CHECK(c1.valid(isec[1]));
    CHECK(c2.valid(isec[1]));
}

// =================================================================================================
IGNORE_TEST_CASE(intersect_circles_outside_each_other_crossing)
{
    Circle c1{Point{5,1}, 5}, c2{Point{1,5}, 3};

    auto isec = intersect(c1, c2);
    CHECK_EQ(isec.size(), 2);
    CHECK_EQ(isec[0], (Point{1, -2}));
    CHECK_EQ(isec[1], (Point{8, 5}));
    CHECK(c1.valid(isec[0]));
    CHECK(c1.valid(isec[1]));
    CHECK_EQ(gk::distance(c2.center, isec[0]), 3);
    CHECK(c2.valid(isec[0]));
    CHECK_EQ(gk::distance(c2.center, isec[1]), 3);
    CHECK(c2.valid(isec[1]));
}
