#include <Shapes.h>

#include "unit_test.h"

using namespace gk;

// =================================================================================================
TEST_CASE(Circle_inside)
{
    Circle c{Point{0,0}, 2};

    CHECK(c.is_inside(Point{0,0}));
    CHECK(c.is_inside(Point{1,1}));
    CHECK(!c.is_inside(Point{2,2}));
    CHECK(!c.is_inside(Point{0,2})); //< NOTE: circumference is not inside
    CHECK(!c.is_inside(Point{2,0}));
    CHECK(c.is_inside(Point{2.0 - 1e-6,0}));
}
