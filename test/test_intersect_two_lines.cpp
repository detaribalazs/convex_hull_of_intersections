#include <Intersections.h>
#include "unit_test.h"

using namespace gk;

// =================================================================================================
TEST_CASE(intersect_line_line_at_edge_1)
{
    LineSegment l1{Point{0,-1}, Point{2,3}};
    LineSegment l2{Point{0, 2}, Point{1,1}};

    CHECK(l1.line().valid(Point{1,1}));
    CHECK(l2.line().valid(Point{1,1}));
    CHECK_EQ(intersect(l1, l2), Intersections(Point{1,1}));
    CHECK_EQ(intersect(l2, l1), Intersections(Point{1,1}));
}

// =================================================================================================
TEST_CASE(intersect_line_line_at_edge_2)
{
    LineSegment l1{Point{1,1}, Point{2,3}};
    LineSegment l2{Point{0, 2}, Point{2,0}};
    LineSegment l3{Point{0, 2}, Point{1,1}};

    CHECK(l1.line().valid(Point{1,1}));
    CHECK(l2.line().valid(Point{1,1}));
    CHECK(l3.line().valid(Point{1,1}));
    CHECK_EQ(intersect(l1, l2), Intersections(Point{1,1}));
    CHECK_EQ(intersect(l1, l3), Intersections(Point{1,1}));
    CHECK_EQ(intersect(l2, l1), Intersections(Point{1,1}));
    CHECK_EQ(intersect(l3, l1), Intersections(Point{1,1}));
}

// =================================================================================================
TEST_CASE(intersect_line_line_in_the_middle_negative_positive_slope)
{
    LineSegment l1{Point{0,-1}, Point{2,3}};
    LineSegment l2{Point{0, 2}, Point{2,0}};

    CHECK(l1.line().valid(Point{1,1}));
    CHECK(l2.line().valid(Point{1,1}));
    CHECK_EQ(intersect(l1, l2), Intersections(Point{1,1}));
}

// =================================================================================================
TEST_CASE(intersect_line_line_in_the_middle_both_slopes_positive)
{
    LineSegment l1{Point{0, 0}, Point{10,10}};
    LineSegment l2{Point{0, 2}, Point{10, 8}};
    LineSegment l3{Point{0, 1}, Point{10, 9}};

    CHECK(l1.line().valid(Point{5,5}));
    CHECK(l2.line().valid(Point{5,5}));
    CHECK(l3.line().valid(Point{5,5}));
    CHECK_EQ(intersect(l1, l2)[0], (Point{5,5}));
    CHECK_EQ(intersect(l1, l3)[0], (Point{5,5}));
    CHECK_EQ(intersect(l2, l1)[0], (Point{5,5}));
    CHECK_EQ(intersect(l3, l1)[0], (Point{5,5}));
}

// =================================================================================================
TEST_CASE(intersect_line_line_in_the_middle_one_is_horizontal)
{
    LineSegment l1a{Point{0, 5}, Point{10, 5}};
    LineSegment l1b{Point{10, 5}, Point{0, 5}};
    LineSegment l2{Point{0, 2}, Point{10, 8}};
    LineSegment l3{Point{0, 1}, Point{10, 9}};

    CHECK(l1a.line().valid(Point{5,5}));
    CHECK(l1b.line().valid(Point{5,5}));
    CHECK(l2.line().valid(Point{5,5}));
    CHECK(l3.line().valid(Point{5,5}));
    CHECK_EQ(intersect(l1a, l2)[0], (Point{5,5}));
    CHECK_EQ(intersect(l1a, l3)[0], (Point{5,5}));
    CHECK_EQ(intersect(l2, l1a)[0], (Point{5,5}));
    CHECK_EQ(intersect(l3, l1a)[0], (Point{5,5}));
    CHECK_EQ(intersect(l1b, l2)[0], (Point{5,5}));
    CHECK_EQ(intersect(l1b, l3)[0], (Point{5,5}));
    CHECK_EQ(intersect(l2, l1b)[0], (Point{5,5}));
    CHECK_EQ(intersect(l3, l1b)[0], (Point{5,5}));
}

// =================================================================================================
TEST_CASE(intersect_line_line_in_the_middle_one_is_vertical)
{
    LineSegment l1a{Point{5, 0}, Point{5, 10}};
    LineSegment l1b{Point{5, 10}, Point{5, 0}};
    LineSegment l2{Point{0, 2}, Point{10, 8}};
    LineSegment l3{Point{0, 1}, Point{10, 9}};

    CHECK(l1a.line().valid(Point{5,5}));
    CHECK(l1b.line().valid(Point{5,5}));
    CHECK(l2.line().valid(Point{5,5}));
    CHECK(l3.line().valid(Point{5,5}));
    CHECK_EQ(intersect(l1a, l2)[0], (Point{5,5}));
    CHECK_EQ(intersect(l1a, l3)[0], (Point{5,5}));
    CHECK_EQ(intersect(l2, l1a)[0], (Point{5,5}));
    CHECK_EQ(intersect(l3, l1a)[0], (Point{5,5}));
    CHECK_EQ(intersect(l1b, l2)[0], (Point{5,5}));
    CHECK_EQ(intersect(l1b, l3)[0], (Point{5,5}));
    CHECK_EQ(intersect(l2, l1b)[0], (Point{5,5}));
    CHECK_EQ(intersect(l3, l1b)[0], (Point{5,5}));
}

// =================================================================================================
TEST_CASE(intersect_line_line_no_intersection_parallel)
{
    LineSegment l1a{Point{0, 1000}, Point{1000, 0}};
    LineSegment l2 {Point{0, 2000}, Point{2000, 0}};
    LineSegment l1b{Point{1000, 0}, Point{0, 1000}};

    CHECK_EQ(intersect(l1a, l2), Intersections());
    CHECK_EQ(intersect(l2, l1a), Intersections());
    CHECK_EQ(intersect(l1b, l2), Intersections());
    CHECK_EQ(intersect(l2, l1b), Intersections());
}

// =================================================================================================
TEST_CASE(intersect_line_line_no_intersection_parallel_vertical)
{
    LineSegment l1a{Point{0, 0}, Point{0, 10}};
    LineSegment l1b{Point{0, 10}, Point{0, 0}};
    LineSegment l2 {Point{2, 0}, Point{2, 10}};

    CHECK_EQ(intersect(l1a, l2), Intersections());
    CHECK_EQ(intersect(l2, l1a), Intersections());
    CHECK_EQ(intersect(l1b, l2), Intersections());
    CHECK_EQ(intersect(l2, l1b), Intersections());
}

// =================================================================================================
TEST_CASE(intersect_line_line_no_intersection_on_same_line)
{
    LineSegment l1{Point{-1, -1}, Point{1, 1}};
    LineSegment l2 {Point{1.1, 1.1}, Point{3, 3}};

    CHECK_EQ(intersect(l1, l2), Intersections());
    CHECK_EQ(intersect(l2, l1), Intersections());
}

// =================================================================================================
TEST_CASE(intersect_line_line_no_intersection_one_ends_before_the_other)
{
    LineSegment l1{Point{-1, -1}, Point{1, 1}};
    LineSegment l2 {Point{0, 3}, Point{3, 0}};

    CHECK_EQ(intersect(l1, l2), Intersections());
    CHECK_EQ(intersect(l2, l1), Intersections());
}
