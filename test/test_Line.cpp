#include <Shapes.h>

#include "unit_test.h"

using namespace gk;

// =================================================================================================
TEST_CASE(Line_line_equation)
{
    // horizontal
    CHECK_EQ(Line(Point{1,5}, Point{8,5}), Line(0, 7, 35));
    // vertical
    CHECK_EQ(Line(Point{5,1}, Point{5,8}), Line(7, 0, 35));

    Line l1{Point{0,0}, Point{2,3}};
    CHECK_EQ(l1, Line(3, -2, 0));
    CHECK_EQ((l1 + Vector{0,1}),  Line(3, -2, -2));
    CHECK_EQ((l1 + Vector{1,0}),  Line(3, -2, 3));
    CHECK_EQ((l1 + Vector{-3,0}),  Line(3, -2, -9));
    CHECK_EQ(Line(Point{-3,1}, Point{-1,4}),  Line(3, -2, -11));
    CHECK_EQ((l1 + Vector{-3,1}),  Line(3, -2, -11));
    CHECK_EQ(Line(Point{0,0}, Point{2,-3}), Line(3, 2, 0));
    CHECK_EQ(Line(Point{0,1}, Point{2,-3}), Line(4, 2, 2));
    CHECK_EQ(Line(Point{1,0}, Point{2,-3}), Line(3, 1, 3));
}

// =================================================================================================
TEST_CASE(Line_equality)
{
    CHECK_EQ(Line({0,0}, {10,5}), Line({10,5}, {0, 0}));
    CHECK_EQ(Line({0,0}, {10,5}), Line({10,5}, {20, 10}));
    CHECK_EQ(Line({0,0}, {10,5}), Line({10,5}, {-20, -10}));
    CHECK_EQ(Line({0,0}, {10,5}), Line({-10,-5}, {-20, -10}));
}

// =================================================================================================
TEST_CASE(Line_equality_horizontal)
{
    CHECK_EQ(Line({0,5}, {10,5}), Line({10,5}, {0, 5}));
    CHECK_EQ(Line({0,5}, {10,5}), Line({10,5}, {20, 5}));
    CHECK_EQ(Line({0,5}, {10,5}), Line({10,5}, {-20, 5}));
    CHECK_EQ(Line({0,5}, {10,5}), Line({-10,5}, {-20, 5}));
}

// =================================================================================================
TEST_CASE(Line_equality_vertical)
{
    CHECK_EQ(Line({10,0}, {10,5}), Line({10,5}, {10, 0}));
    CHECK_EQ(Line({10,0}, {10,5}), Line({10,5}, {10, 10}));
    CHECK_EQ(Line({10,0}, {10,5}), Line({10,5}, {10, -10}));
    CHECK_EQ(Line({10,0}, {10,5}), Line({10,-5}, {10, -10}));
}

// =================================================================================================
TEST_CASE(Line_point_validity)
{
    Line l1({0,0}, {10,5});
    CHECK(l1.valid({0.0, 0.0}));
    CHECK(l1.valid({5.0, 2.5}));

    {
        Line l = l1 + Vector{2, 0};
        CHECK(l.valid({2.0, 0.0}));
        CHECK(l.valid({7.0, 2.5}));
    }

    {
        Line l = l1 + Vector{0, 3};
        CHECK(l.valid({0.0, 3.0}));
        CHECK(l.valid({5.0, 5.5}));
    }

    {
        Line l = l1 + Vector{2, 3};
        CHECK(l.valid({2.0, 3.0}));
        CHECK(l.valid({7.0, 5.5}));
    }
}

// =================================================================================================
TEST_CASE(Line_translation_and_slopes)
{
    Line l1({0,0}, {10,5});

    {
        CHECK_EQ(l1.slope_y(), 0.5);
        CHECK_EQ(l1.slope_x(), 2.0);
        CHECK_EQ(l1.get_y(5.0), 2.5);
        CHECK_EQ(l1.get_x(2.5), 5.0);
    }

    {
        Line l = l1 + Vector{2, 0};

        CHECK_EQ(l.slope_y(), 0.5);
        CHECK_EQ(l.slope_x(), 2.0);
        CHECK_EQ(l.get_y(5.0 + 2.0), 2.5);
        CHECK_EQ(l.get_x(2.5), 5.0 + 2.0);
    }

    {
        Line l = l1 + Vector{0, 3};

        CHECK_EQ(l.slope_y(), 0.5);
        CHECK_EQ(l.slope_x(), 2.0);
        CHECK_EQ(l.get_y(5.0), 2.5 + 3.0);
        CHECK_EQ(l.get_x(2.5 + 3.0), 5.0);
    }

    {
        Line l = l1 + Vector{2, 3};

        CHECK_EQ(l.slope_y(), 0.5);
        CHECK_EQ(l.slope_x(), 2.0);
        CHECK_EQ(l.get_y(5.0 + 2.0), 2.5 + 3.0);
        CHECK_EQ(l.get_x(2.5 + 3.0), 5.0 + 2.0);
    }
}
