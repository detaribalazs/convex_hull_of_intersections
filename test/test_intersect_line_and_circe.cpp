#include <Intersections.h>
#include "unit_test.h"

using namespace gk;

// =================================================================================================
TEST_CASE(intersect_line_circle_transitive)
{
    LineSegment l{Point{1,-10}, Point{1,10}};
    Circle c{Point{0,0}, 2};

    CHECK_EQ(intersect(l,c), intersect(c,l));
}

// =================================================================================================
TEST_CASE(intersect_line_circle_inside)
{
    LineSegment l{Point{2,-10}, Point{2,10}};
    Circle c{Point{0,0}, 15};

    CHECK_EQ(intersect(l,c).size(), 0);
}

// =================================================================================================
TEST_CASE(intersect_line_circle_no_crossing)
{
    LineSegment l{Point{0,10}, Point{12,1}};
    Circle c{Point{0,0}, 5};

    CHECK_EQ(intersect(l,c).size(), 0);
}

// =================================================================================================
TEST_CASE(intersect_line_circle_origo_based_vertical_tangent)
{
    LineSegment l{Point{2,-10}, Point{2,10}};
    Circle c{Point{0,0}, 2};

    auto isec = intersect(l,c);
    CHECK_EQ(isec.size(), 1);
    CHECK(l.line().valid(isec[0]));
    CHECK(c.valid(isec[0]));
    CHECK_EQ(isec[0], (Point{2,0}));
}

// =================================================================================================
TEST_CASE(intersect_line_circle_origo_based_vertical_full_crossing)
{
    LineSegment l{Point{0,-10}, Point{0,10}};
    Circle c{Point{0,0}, 3};

    auto isec = intersect(l,c);
    CHECK_EQ(isec.size(), 2);
    CHECK(l.line().valid(isec[0]));
    CHECK(l.line().valid(isec[1]));
    CHECK(c.valid(isec[0]));
    CHECK(c.valid(isec[1]));
    CHECK_EQ(isec[0], (Point{0, +3}));
    CHECK_EQ(isec[1], (Point{0, -3}));
}

// =================================================================================================
TEST_CASE(intersect_line_circle_origo_based_vertical_upper_half_crossing)
{
    LineSegment l{Point{0,1}, Point{0,10}};
    Circle c{Point{0,0}, 3};

    auto isec = intersect(l,c);
    CHECK_EQ(isec.size(), 1);
    CHECK(l.line().valid(isec[0]));
    CHECK(c.valid(isec[0]));
    CHECK_EQ(isec[0], (Point{0, +3}));
}

// =================================================================================================
TEST_CASE(intersect_line_circle_origo_based_vertical_lower_half_crossing)
{
    LineSegment l{Point{0,1}, Point{0,-10}};
    Circle c{Point{0,0}, 3};

    auto isec = intersect(l,c);
    CHECK_EQ(isec.size(), 1);
    CHECK(l.line().valid(isec[0]));
    CHECK(c.valid(isec[0]));
    CHECK_EQ(isec[0], (Point{0, -3}));
}

// =================================================================================================
TEST_CASE(intersect_line_circle_vertical_tangent_translated)
{
    LineSegment l{Point{6,-10}, Point{6,10}};
    Circle c{Point{4,2}, 2};

    auto isec = intersect(l,c);
    CHECK_EQ(isec.size(), 1);
    CHECK(l.line().valid(isec[0]));
    CHECK(c.valid(isec[0]));
    CHECK_EQ(isec[0], (Point{6,2}));
}

// =================================================================================================
TEST_CASE(intersect_line_circle_vertical_full_crossing_translated)
{
    LineSegment l{Point{3,-10}, Point{3,10}};
    Circle c{Point{3,1}, 3};

    auto isec = intersect(l,c);
    CHECK_EQ(isec.size(), 2);
    CHECK(l.line().valid(isec[0]));
    CHECK(l.line().valid(isec[1]));
    CHECK(c.valid(isec[0]));
    CHECK(c.valid(isec[1]));
    CHECK_EQ(isec[0], (Point{3, +4}));
    CHECK_EQ(isec[1], (Point{3, -2}));
}

// =================================================================================================
TEST_CASE(intersect_line_circle_vertical_upper_half_crossing_translated)
{
    LineSegment l{Point{3,1}, Point{3,10}};
    Circle c{Point{3,1}, 3};

    auto isec = intersect(l,c);
    CHECK_EQ(isec.size(), 1);
    CHECK(l.line().valid(isec[0]));
    CHECK(c.valid(isec[0]));
    CHECK_EQ(isec[0], (Point{3, +4}));
}

// =================================================================================================
TEST_CASE(intersect_line_circle_origo_based_generic_tangent)
{
    const float r = 5.0;
    const float sqrt2 = sqrt(2.0);
    LineSegment l{Point{0, sqrt2 * r}, Point{sqrt2*r, 0}};
    Circle c{Point{0,0}, r};

    auto ln = l.line();
    auto isec = intersect(l,c);
    CHECK_EQ(isec.size(), 1);
    CHECK_EQ(ln.a * isec[0].x + ln.b * isec[0].y, ln.c);
    CHECK(l.line().valid(isec[0]));
    CHECK(c.valid(isec[0]));
    CHECK_EQ(isec[0], (Point{sqrt2 * r / 2.0f, sqrt2 * r / 2.0f}));
}

// =================================================================================================
TEST_CASE(intersect_line_circle_origo_based_generic_crossing)
{
    const float r = 5.0;
    const float sqrt2 = sqrt(2.0);
    LineSegment l{Point{0, sqrt2 * r - 1}, Point{sqrt2*r - 1, 0}};
    Circle c{Point{0,0}, r};

    auto isec = intersect(l,c);
    CHECK_EQ(isec.size(), 2);
    CHECK(l.line().valid(isec[0]));
    CHECK(l.line().valid(isec[1]));
    CHECK(c.valid(isec[0]));
    CHECK(c.valid(isec[1]));
    CHECK_EQ(std::max(isec[0], isec[1]), (Point{4.84814, 1.22293}));
    CHECK_EQ(std::min(isec[0], isec[1]), (Point{1.22293, 4.84814}));
}

// =================================================================================================
TEST_CASE(intersect_line_circle_origo_based_generic_upper_half_crossing)
{
    LineSegment l{Point{0, 7}, Point{3, 3}};
    Circle c{Point{0,0}, 5};

    auto isec = intersect(l,c);
    CHECK_EQ(isec.size(), 1);
    CHECK(l.line().valid(isec[0]));
    CHECK(c.valid(isec[0]));
    CHECK_EQ(isec[0], (Point{1.73224, 4.69035}));
}

// =================================================================================================
TEST_CASE(intersect_line_circle_origo_based_generic_crossing_backward_line)
{
    const float r = 5.0;
    const float sqrt2 = sqrt(2.0);
    LineSegment l{Point{sqrt2 * r - 1, 0}, Point{0, sqrt2*r - 1}};
    Circle c{Point{0,0}, r};

    auto isec = intersect(l,c);
    CHECK_EQ(isec.size(), 2);
    CHECK(l.line().valid(isec[0]));
    CHECK(l.line().valid(isec[1]));
    CHECK(c.valid(isec[0]));
    CHECK(c.valid(isec[1]));
    CHECK_EQ(std::max(isec[0], isec[1]), (Point{4.84814, 1.22293}));
    CHECK_EQ(std::min(isec[0], isec[1]), (Point{1.22293, 4.84814}));
}

// =================================================================================================
TEST_CASE(intersect_line_circle_origo_based_upper_crossing_positive_slope)
{
    LineSegment l{Point{0, 0}, Point{10, 10}};
    Circle c{Point{0,0}, 6};
    const float srr = sqrt(c.radius * c.radius / 2.0);

    auto isec = intersect(l,c);
    CHECK_EQ(isec.size(), 1);
    CHECK(l.line().valid(isec[0]));
    CHECK(c.valid(isec[0]));
    CHECK_EQ(isec[0], (Point{srr, srr}));
}

// =================================================================================================
TEST_CASE(intersect_line_circle_origo_based_lower_crossing_positive_slope)
{
    LineSegment l{Point{0, 0}, Point{-10, -10}};
    Circle c{Point{0,0}, 6};
    const float srr = sqrt(c.radius * c.radius / 2.0);

    auto isec = intersect(l,c);
    CHECK_EQ(isec.size(), 1);
    CHECK(l.line().valid(isec[0]));
    CHECK(c.valid(isec[0]));
    CHECK_EQ(isec[0], (Point{-srr, -srr}));
}

// =================================================================================================
TEST_CASE(intersect_line_circle_origo_based_full_crossing_positive_slope)
{
    LineSegment l{Point{-10, -10}, Point{10, 10}};
    Circle c{Point{0,0}, 6};
    const float srr = sqrt(c.radius * c.radius / 2.0);

    auto isec = intersect(l,c);
    CHECK_EQ(isec.size(), 2);
    CHECK(l.line().valid(isec[0]));
    CHECK(l.line().valid(isec[1]));
    CHECK(c.valid(isec[0]));
    CHECK(c.valid(isec[1]));
    CHECK_EQ(isec[0], (Point{srr, srr}));
    CHECK_EQ(isec[1], (Point{-srr, -srr}));
}

// =================================================================================================
TEST_CASE(intersect_line_circle_origo_based_horizontal_tangent)
{
    LineSegment l{Point{-10, 2}, Point{10, 2}};
    Circle c{Point{0,0}, 2};

    auto isec = intersect(l,c);
    CHECK_EQ(isec.size(), 1);
    CHECK_EQ(isec[0], (Point{0,2}));
    CHECK(l.line().valid(isec[0]));
    CHECK(c.valid(isec[0]));
}

// =================================================================================================
TEST_CASE(intersect_line_circle_origo_based_horizontal_full_crossing)
{
    LineSegment l{Point{-10, 0}, Point{10, 0}};
    Circle c{Point{0,0}, 3};

    auto isec = intersect(l,c);
    CHECK_EQ(isec.size(), 2);
    CHECK(l.line().valid(isec[0]));
    CHECK(l.line().valid(isec[1]));
    CHECK(c.valid(isec[0]));
    CHECK(c.valid(isec[1]));
    CHECK_EQ(isec[0], (Point{-3, 0}));
    CHECK_EQ(isec[1], (Point{+3, 0}));
}

// =================================================================================================
TEST_CASE(intersect_line_circle_horizontal_full_crossing_translated)
{
    LineSegment l{Point{-10, 1}, Point{10, 1}};
    Circle c{Point{3,1}, 2};

    auto isec = intersect(l,c);
    CHECK_EQ(isec.size(), 2);
    CHECK(l.line().valid(isec[0]));
    CHECK(l.line().valid(isec[1]));
    CHECK(c.valid(isec[0]));
    CHECK(c.valid(isec[1]));
    CHECK_EQ(isec[0], (Point{1, 1}));
    CHECK_EQ(isec[1], (Point{5, 1}));
}

// =================================================================================================
TEST_CASE(intersect_line_circle_horizontal_tangent_translated)
{
    LineSegment l{Point{-10, 3}, Point{10, 3}};
    Circle c{Point{3,1}, 2};

    auto isec = intersect(l,c);
    CHECK_EQ(isec.size(), 1);
    CHECK(l.line().valid(isec[0]));
    CHECK(c.valid(isec[0]));
    CHECK_EQ(isec[0], (Point{3, 3}));
}

// =================================================================================================
TEST_CASE(intersect_infinite_horizontal_line_and_circle_origo_based)
{
    Line l{Point{-10, 0}, Point{10, 0}};
    Circle c{Point{0,0}, 3};

    auto isec = intersect(l,c);
    CHECK_EQ(isec.size(), 2);
    CHECK(l.valid(isec[0]));
    CHECK(l.valid(isec[1]));
    CHECK(c.valid(isec[0]));
    CHECK(c.valid(isec[1]));
    CHECK_EQ(isec[0], (Point{-3, 0}));
    CHECK_EQ(isec[1], (Point{+3, 0}));
}

// =================================================================================================
TEST_CASE(intersect_infinite_horizontal_line_and_circle_shift_y)
{
    Line l{Point{-10, 3}, Point{10, 3}};
    Circle c{Point{0, 3}, 3};

    auto isec = intersect(l,c);
    CHECK_EQ(isec.size(), 2);
    CHECK(l.valid(isec[0]));
    CHECK(l.valid(isec[1]));
    CHECK(c.valid(isec[0]));
    CHECK(c.valid(isec[1]));
    CHECK_EQ(isec[0], (Point{-3, 3}));
    CHECK_EQ(isec[1], (Point{+3, 3}));
}

// =================================================================================================
TEST_CASE(intersect_infinite_horizontal_line_and_circle_shift_x)
{
    Line l{Point{-13, 0}, Point{13, 0}};
    Circle c{Point{3,0}, 3};

    auto isec = intersect(l,c);
    CHECK_EQ(isec.size(), 2);
    CHECK(l.valid(isec[0]));
    CHECK(l.valid(isec[1]));
    CHECK(c.valid(isec[0]));
    CHECK(c.valid(isec[1]));
    CHECK_EQ(isec[0], (Point{0, 0}));
    CHECK_EQ(isec[1], (Point{6, 0}));
}

// =================================================================================================
TEST_CASE(intersect_infinite_horizontal_line_and_circle_shift_xy)
{
    Line l{Point{-13, 3}, Point{13, 3}};
    Circle c{Point{3,3}, 3};

    auto isec = intersect(l,c);
    CHECK_EQ(isec.size(), 2);
    CHECK(l.valid(isec[0]));
    CHECK(l.valid(isec[1]));
    CHECK(c.valid(isec[0]));
    CHECK(c.valid(isec[1]));
    CHECK_EQ(isec[0], (Point{0, 3}));
    CHECK_EQ(isec[1], (Point{6, 3}));
}

// =================================================================================================
TEST_CASE(intersect_infinite_horizontal_line_and_circle_shift_xy_and_circle)
{
    Line l{Point{-13, 3}, Point{13, 3}};
    Circle c{Point{3,1}, 3};

    auto isec = intersect(l,c);
    CHECK_EQ(isec.size(), 2);
    CHECK(l.valid(isec[0]));
    CHECK(l.valid(isec[1]));
    CHECK(c.valid(isec[0]));
    CHECK(c.valid(isec[1]));
    CHECK_EQ(isec[0], (Point{0.763932, 3}));
    CHECK_EQ(isec[1], (Point{5.23607, 3}));
}

// =================================================================================================
TEST_CASE(intersect_infinite_vertical_line_and_circle_shift_xy)
{
    Line l{Point{3, -3}, Point{3, 3}};
    Circle c{Point{3,3}, 3};

    auto isec = intersect(l,c);
    CHECK_EQ(isec.size(), 2);
    CHECK(l.valid(isec[0]));
    CHECK(l.valid(isec[1]));
    CHECK(c.valid(isec[0]));
    CHECK(c.valid(isec[1]));
    CHECK_EQ(isec[0], (Point{3, 6}));
    CHECK_EQ(isec[1], (Point{3, 0}));
}

// =================================================================================================
TEST_CASE(intersect_infinite_horizontal_line_and_circle_tangent)
{
    Line l{Point{-10, 3}, Point{10, 3}};
    Circle c{Point{3,1}, 2};

    auto isec = intersect(l,c);
    CHECK_EQ(isec.size(), 1);
    CHECK(l.valid(isec[0]));
    CHECK(c.valid(isec[0]));
    CHECK_EQ(isec[0], (Point{3, 3}));
}

// =================================================================================================
TEST_CASE(intersect_infinite_line_and_circle_crossing)
{
    Line l{Point{-1, 7}, Point{13, -5}};
    Circle c{Point{3,1}, 4};

    auto isec = intersect(l,c);
    CHECK_EQ(isec.size(), 2);
    CHECK(c.valid(isec[0]));
    CHECK(c.valid(isec[1]));
    CHECK_EQ(l.a * isec[0].x + l.b * isec[0].y, l.c);
    CHECK_EQ(l.a * isec[1].x + l.b * isec[1].y, l.c);
    CHECK(l.valid(isec[0]));
    CHECK(l.valid(isec[1]));
    CHECK_EQ(isec[0], (Point{1.6199, 4.75437}));
    CHECK_EQ(isec[1], (Point{6.92128, 0.210333}));
}
