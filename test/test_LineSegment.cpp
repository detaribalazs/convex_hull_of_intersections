#include <Shapes.h>

#include "unit_test.h"

using namespace gk;

// =================================================================================================
TEST_CASE(LineSegment_point_validity)
{
    LineSegment l1({0,0}, {10,5});
    CHECK(l1.valid({ 0.0, 0.0}));
    CHECK(l1.valid({ 5.0, 2.5}));
    CHECK(l1.valid({10.0, 5.0}));
    CHECK(l1.line().valid({-10.0, -5.0}));
    CHECK(l1.line().valid({20.0, 10.0}));
    CHECK(!l1.valid({-10.0, -5.0}));
    CHECK(!l1.valid({20.0, 10.0}));

    {
        LineSegment l = l1 + Vector{2, 0};
        CHECK(l.valid({2.0, 0.0}));
        CHECK(l.valid({7.0, 2.5}));
        CHECK(l.valid({12.0, 5.0}));
        CHECK(l.line().valid({-8.0, -5.0}));
        CHECK(l.line().valid({22.0, 10.0}));
        CHECK(!l.valid({-8.0, -5.0}));
        CHECK(!l.valid({22.0, 10.0}));
    }

    {
        LineSegment l = l1 + Vector{0, 3};
        CHECK(l.valid({0.0, 3.0}));
        CHECK(l.valid({5.0, 5.5}));
        CHECK(l.valid({10.0, 8.0}));
        CHECK(l.line().valid({-10.0, -2.0}));
        CHECK(l.line().valid({20.0, 13.0}));
        CHECK(!l.valid({-10.0, -2.0}));
        CHECK(!l.valid({20.0, 13.0}));
    }

    {
        LineSegment l = l1 + Vector{2, 3};
        CHECK(l.valid({2.0, 3.0}));
        CHECK(l.valid({7.0, 5.5}));
        CHECK(l.valid({12.0, 8.0}));
        CHECK(l.line().valid({-8.0, -2.0}));
        CHECK(l.line().valid({22.0, 13.0}));
        CHECK(!l.valid({-8.0, -2.0}));
        CHECK(!l.valid({22.0, 13.0}));
    }
}

// =================================================================================================
TEST_CASE(LineSegment_translation_and_slopes)
{
    LineSegment l1({0,0}, {10,5});

    {
        CHECK_EQ(l1.line().slope_y(), 0.5);
        CHECK_EQ(l1.line().slope_x(), 2.0);
        CHECK_EQ(l1.line().get_y(5.0), 2.5);
        CHECK_EQ(l1.line().get_x(2.5), 5.0);
    }

    {
        LineSegment l = l1 + Vector{2, 0};

        CHECK_EQ(l.line().slope_y(), 0.5);
        CHECK_EQ(l.line().slope_x(), 2.0);
        CHECK_EQ(l.line().get_y(5.0 + 2.0), 2.5);
        CHECK_EQ(l.line().get_x(2.5), 5.0 + 2.0);
    }

    {
        LineSegment l = l1 + Vector{0, 3};

        CHECK_EQ(l.line().slope_y(), 0.5);
        CHECK_EQ(l.line().slope_x(), 2.0);
        CHECK_EQ(l.line().get_y(5.0), 2.5 + 3.0);
        CHECK_EQ(l.line().get_x(2.5 + 3.0), 5.0);
    }

    {
        LineSegment l = l1 + Vector{2, 3};

        CHECK_EQ(l.line().slope_y(), 0.5);
        CHECK_EQ(l.line().slope_x(), 2.0);
        CHECK_EQ(l.line().get_y(5.0 + 2.0), 2.5 + 3.0);
        CHECK_EQ(l.line().get_x(2.5 + 3.0), 5.0 + 2.0);
    }
}
