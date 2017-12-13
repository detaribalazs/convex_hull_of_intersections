#include <Shapes.h>

#include "unit_test.h"

using namespace gk;

// =================================================================================================
TEST_CASE(LineSegment_deltas)
{
    {
        LineSegment l{Point{0,-1}, Point{2,3}};

        CHECK_EQ(l.delta_y(), 4.0);
        CHECK_EQ(l.delta_x(), 2.0);
    }

    {
        LineSegment l{Point{-3,1}, Point{2,0}};

        CHECK_EQ(l.delta_y(), -1.0);
        CHECK_EQ(l.delta_x(), 5.0);
    }
}

// =================================================================================================
TEST_CASE(LineSegment_slope)
{
    {
        LineSegment l{Point{0,-1}, Point{2,3}};
        CHECK_EQ(l.slope_y(), 2.0);
        CHECK_EQ(l.slope_x(), .5);
        CHECK_EQ(l.slope_y(), l.line().slope_y());
        CHECK_EQ(l.slope_x(), l.line().slope_x());
    }

    {
        LineSegment l{Point{-3,1}, Point{2,0}};
        CHECK_EQ(l.slope_y(), -0.2);
        CHECK_EQ(l.slope_x(), -5);
        CHECK_EQ(l.slope_y(), l.line().slope_y());
        CHECK_EQ(l.slope_x(), l.line().slope_x());
    }

    {
        LineSegment l{Point{0,5}, Point{2,5}};
        CHECK_EQ(l.slope_y(), 0.0);
        CHECK_EQ(l.slope_x(), test::pos_inf);
        CHECK_EQ(l.slope_y(), l.line().slope_y());
        CHECK_EQ(l.slope_x(), l.line().slope_x());
    }

    {
        LineSegment l{Point{5,0}, Point{5,9}};
        CHECK_EQ(l.slope_y(), test::pos_inf);
        CHECK_EQ(l.slope_x(), 0.0);
        CHECK_EQ(l.slope_y(), l.line().slope_y());
        CHECK_EQ(l.slope_x(), l.line().slope_x());
    }

    {
        LineSegment l{Point{5,9}, Point{5,-1}};
        CHECK_EQ(l.slope_y(), test::pos_inf);
        CHECK_EQ(l.slope_x(), 0.0);
        CHECK_EQ(l.slope_y(), l.line().slope_y());
        CHECK_EQ(l.slope_x(), l.line().slope_x());
    }
}

// =================================================================================================
TEST_CASE(LineSegment_get_y)
{
    {
        LineSegment l{Point{0,-1}, Point{2,3}};

        CHECK_EQ(l.get_y(0.0), -1.0);
        CHECK_EQ(l.get_y(1.0), 1.0);
        CHECK_EQ(l.get_y(2.0), 3.0);
    }

    {
        LineSegment l{Point{-3,1}, Point{2,0}};

        CHECK_EQ(l.get_y(-3.0), 1.0);
        CHECK_EQ(l.get_y(-1.0), 0.6);
        CHECK_EQ(l.get_y(1.0), 0.2);
        CHECK_EQ(l.get_y(2.0), 0.0);
    }
}

// =================================================================================================
TEST_CASE(LineSegment_valid_x)
{
    {
        LineSegment l{Point{0,-1}, Point{2,3}};

        CHECK(l.valid_x(0.0));
        CHECK(l.valid_x(1.0));
        CHECK(l.valid_x(2.0));
    }

    {
        LineSegment l{Point{-3,1}, Point{2,0}};

        CHECK(l.valid_x(-3.0));
        CHECK(l.valid_x(-1.0));
        CHECK(l.valid_x(1.0));
        CHECK(l.valid_x(2.0));
    }
}

// =================================================================================================
TEST_CASE(LineSegment_valid_y)
{
    {
        LineSegment l{Point{0,-1}, Point{2,3}};

        CHECK(l.valid_y(-1.0));
        CHECK(l.valid_y(1.0));
        CHECK(l.valid_y(3.0));
    }

    {
        LineSegment l{Point{-3,1}, Point{2,0}};

        CHECK(l.valid_y(1.0));
        CHECK(l.valid_y(0.5));
        CHECK(l.valid_y(0.0));
    }
}

// =================================================================================================
TEST_CASE(LineSegment_line_equation)
{
    {
        // horizontal
        LineSegment l{Point{1,5}, Point{8,5}};

        CHECK_EQ(l.delta_y(), 0);
        CHECK_EQ(l.delta_x(), 7);
        CHECK_EQ(l.slope_y(), 0.0);
        CHECK_EQ(l.slope_x(), test::pos_inf);
        CHECK_EQ(l.line().a, 0);
        CHECK_EQ(l.line().b, 7);
        CHECK_EQ(l.line().c,35);
        CHECK(l.line().valid(l[0]));
        CHECK(l.line().valid(l[1]));
        CHECK(l.line().valid(l[0] + Vector{11,0}));
        CHECK(l.line().valid(l[0] - Vector{11,0}));
    }

    {
        // vertical
        LineSegment l{Point{5,1}, Point{5,8}};

        CHECK_EQ(l.delta_y(), 7);
        CHECK_EQ(l.delta_x(), 0);
        CHECK_EQ(l.slope_y(), test::pos_inf);
        CHECK_EQ(l.slope_x(), 0.0);
        CHECK_EQ(l.line().a, 7);
        CHECK_EQ(l.line().b, 0);
        CHECK_EQ(l.line().c,35);
        CHECK(l.line().valid(l[0]));
        CHECK(l.line().valid(l[1]));
        CHECK(l.line().valid(l[0] + Vector{0,11}));
        CHECK(l.line().valid(l[1] - Vector{0,11}));
    }

    LineSegment l1{Point{0,0}, Point{2,3}};

    {
        CHECK_EQ(l1.slope_y(), 3.0 / 2.0);
        CHECK_EQ(l1.slope_x(), 2.0 / 3.0);
        CHECK(l1.line().valid(l1[0]));
        CHECK(l1.line().valid(l1[1]));
        CHECK_EQ(l1.line().a,  3);
        CHECK_EQ(l1.line().b, -2);
        CHECK_EQ(l1.line().c,  0);
    }

    {
        auto l = l1 + Vector{0,1};

        CHECK_EQ(l.delta_y(), 3);
        CHECK_EQ(l.delta_x(), 2);
        CHECK_EQ(l.slope_y(), 3.0 / 2.0);
        CHECK(l.line().valid(l[0]));
        CHECK(l.line().valid(l[1]));
        CHECK_EQ(l.line().a,  3);
        CHECK_EQ(l.line().b, -2);
        CHECK_EQ(l.line().c, -2);
    }

    {
        auto l = l1 + Vector{1,0};

        CHECK_EQ(l.delta_y(), 3);
        CHECK_EQ(l.delta_x(), 2);
        CHECK_EQ(l.slope_y(), 3.0 / 2.0);
        CHECK(l.line().valid(l[0]));
        CHECK(l.line().valid(l[1]));
        CHECK_EQ(l.line().a,  3);
        CHECK_EQ(l.line().b, -2);
        CHECK_EQ(l.line().c,  3);
    }

    {
        auto l = l1 + Vector{-3,0};

        CHECK_EQ(l.delta_y(), 3);
        CHECK_EQ(l.delta_x(), 2);
        CHECK_EQ(l.slope_y(), 3.0 / 2.0);
        CHECK(l.line().valid(l[0]));
        CHECK(l.line().valid(l[1]));
        CHECK_EQ(l.line().a,  3);
        CHECK_EQ(l.line().b, -2);
        CHECK_EQ(l.line().c, -9);
    }

    {
        LineSegment l{Point{-3,1}, Point{-1,4}};

        CHECK_EQ(l.delta_y(), 3);
        CHECK_EQ(l.delta_x(), 2);
        CHECK_EQ(l.slope_y(), 3.0 / 2.0);
        CHECK_EQ(l.line().a,  3);
        CHECK_EQ(l.line().b, -2);
        CHECK_EQ(l.line().c,-11);
        CHECK(l.line().valid(l[0]));
        CHECK(l.line().valid(l[1]));
    }

    {
        auto l = l1 + Vector{-3,1};

        CHECK_EQ(l.slope_y(), 3.0 / 2.0);
        CHECK(l.line().valid(l[0]));
        CHECK(l.line().valid(l[1]));
        CHECK_EQ(l.line().a,  3);
        CHECK_EQ(l.line().b, -2);
        CHECK_EQ(l.line().c,-11);
    }

    {
        LineSegment l{Point{0,0}, Point{2,-3}};

        CHECK_EQ(l.slope_y(), -3.0 / 2.0);
        CHECK(l.line().valid(l[0]));
        CHECK(l.line().valid(l[1]));
        CHECK_EQ(l.line().a, 3);
        CHECK_EQ(l.line().b, 2);
        CHECK_EQ(l.line().c, 0);
    }

    {
        LineSegment l{Point{0,1}, Point{2,-3}};

        CHECK_EQ(l.slope_y(), -2.0);
        CHECK(l.line().valid(l[0]));
        CHECK(l.line().valid(l[1]));
        CHECK_EQ(l.line().a, 4);
        CHECK_EQ(l.line().b, 2);
        CHECK_EQ(l.line().c, 2);
    }

    {
        LineSegment l{Point{1,0}, Point{2,-3}};

        CHECK_EQ(l.slope_y(), -3.0);
        CHECK(l.line().valid(l[0]));
        CHECK(l.line().valid(l[1]));
        CHECK_EQ(l.line().a, 3);
        CHECK_EQ(l.line().b, 1);
        CHECK_EQ(l.line().c, 3);
    }
}
