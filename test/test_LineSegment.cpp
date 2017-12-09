#include <Shapes.h>

#include "unit_test.h"

using namespace gk;

// =================================================================================================
TEST_CASE(LineSegment_deltas)
{
    LineSegment l1{Point{0,-1}, Point{2,3}};

    CHECK_EQ(l1.delta_y(), 4.0);
    CHECK_EQ(l1.delta_x(), 2.0);

    LineSegment l2{Point{-3,1}, Point{2,0}};

    CHECK_EQ(l2.delta_y(), -1.0);
    CHECK_EQ(l2.delta_x(), 5.0);
}

// =================================================================================================
TEST_CASE(LineSegment_slope)
{
    LineSegment l1{Point{0,-1}, Point{2,3}};
    CHECK_EQ(l1.slope(), 2.0);

    LineSegment l2{Point{-3,1}, Point{2,0}};
    CHECK_EQ(l2.slope(), -0.2);

    LineSegment l3{Point{0,5}, Point{2,5}};
    CHECK_EQ(l3.slope(), 0.0);

    LineSegment l4{Point{5,0}, Point{5,9}};
    CHECK_EQ(l4.slope(), test::pos_inf);

    LineSegment l5{Point{5,9}, Point{5,-1}};
    CHECK_EQ(l5.slope(), test::neg_inf);
}

// =================================================================================================
TEST_CASE(LineSegment_get_y)
{
    LineSegment l1{Point{0,-1}, Point{2,3}};

    CHECK_EQ(l1.get_y(0.0), -1.0);
    CHECK_EQ(l1.get_y(1.0), 1.0);
    CHECK_EQ(l1.get_y(2.0), 3.0);

    LineSegment l2{Point{-3,1}, Point{2,0}};

    CHECK_EQ(l2.get_y(-3.0), 1.0);
    CHECK_EQ(l2.get_y(-1.0), 0.6);
    CHECK_EQ(l2.get_y(1.0), 0.2);
    CHECK_EQ(l2.get_y(2.0), 0.0);
}

// =================================================================================================
TEST_CASE(LineSegment_valid_x)
{
    LineSegment l1{Point{0,-1}, Point{2,3}};

    CHECK(l1.valid_x(0.0));
    CHECK(l1.valid_x(1.0));
    CHECK(l1.valid_x(2.0));

    LineSegment l2{Point{-3,1}, Point{2,0}};

    CHECK(l2.valid_x(-3.0));
    CHECK(l2.valid_x(-1.0));
    CHECK(l2.valid_x(1.0));
    CHECK(l2.valid_x(2.0));
}
