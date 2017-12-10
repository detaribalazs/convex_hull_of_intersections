#include <Intersections.h>
#include "unit_test.h"

using namespace gk;

// =================================================================================================
TEST_CASE(Intersections_construction_0_param)
{
    Intersections intersections;

    CHECK(intersections.empty());
    CHECK_EQ(intersections.size(), 0);
    CHECK_EQ(std::distance(intersections.begin(), intersections.end()), 0);
}

// =================================================================================================
TEST_CASE(Intersections_construction_1_param)
{
    Point p1{1.0, 1.0};
    Intersections intersections(p1);

    CHECK(!intersections.empty());
    CHECK_EQ(intersections.size(), 1);
    CHECK_EQ(intersections[0], p1);
    CHECK_EQ(std::distance(intersections.begin(), intersections.end()), 1);
}

// =================================================================================================
TEST_CASE(Intersections_construction_2_param)
{
    Point p1{1.0, 1.0};
    Point p2{2.0, 2.0};
    Intersections intersections(p1, p2);

    CHECK(!intersections.empty());
    CHECK_EQ(intersections.size(), 2);
    CHECK_EQ(intersections[0], p1);
    CHECK_EQ(intersections[1], p2);
    CHECK_EQ(std::distance(intersections.begin(), intersections.end()), 2);
}

// =================================================================================================
TEST_CASE(Intersections_add_0)
{
    Point p1{1.0, 1.0};
    Intersections intersections;
    intersections.add(p1);

    CHECK(!intersections.empty());
    CHECK_EQ(intersections.size(), 1);
    CHECK_EQ(intersections[0], p1);
    CHECK_EQ(std::distance(intersections.begin(), intersections.end()), 1);
}

// =================================================================================================
TEST_CASE(Intersections_add_1)
{
    Point p1{1.0, 1.0};
    Point p2{2.0, 2.0};
    Intersections intersections(p1);
    intersections.add(p2);

    CHECK(!intersections.empty());
    CHECK_EQ(intersections.size(), 2);
    CHECK_EQ(intersections[0], p1);
    CHECK_EQ(intersections[1], p2);
    CHECK_EQ(std::distance(intersections.begin(), intersections.end()), 2);
}

// =================================================================================================
TEST_CASE(Intersections_equality)
{
    Point p1{1.0, 1.0};
    Point p2{2.0, 2.0};

    CHECK_EQ(Intersections(), Intersections());
    CHECK_EQ(Intersections(p1), Intersections(p1));
    CHECK_EQ(Intersections(p1,p2), Intersections(p1,p2));
    CHECK(Intersections(p1) != Intersections(p2));
    CHECK(Intersections(p1,p2) != Intersections(p2,p1)); //< NOTE: order of points matters!
    CHECK(Intersections(p1,p2) != Intersections(p1));
    CHECK(Intersections(p1,p2) != Intersections(p2));
}

// =================================================================================================
TEST_CASE(Intersections_erase_empty)
{
    Intersections isec;

    CHECK(isec.empty());
    CHECK(isec.begin() == isec.end());

    CHECK(isec.erase(isec.begin()) == isec.end());

    CHECK(isec.empty());
    CHECK(isec.begin() == isec.end());
}

// =================================================================================================
TEST_CASE(Intersections_erase_single)
{
    Point p1{1.0, 1.0};

    Intersections isec(p1);

    CHECK(!isec.empty());
    CHECK_EQ(isec[0], p1);
    CHECK_EQ(isec.size(), 1);
    CHECK(isec.begin() != isec.end());

    CHECK(isec.erase(isec.begin()) == isec.end());

    CHECK(isec.empty());
    CHECK(isec.begin() == isec.end());
}

// =================================================================================================
TEST_CASE(Intersections_erase_second)
{
    Point p1{1.0, 1.0};
    Point p2{2.0, 2.0};

    Intersections isec(p1, p2);

    CHECK(!isec.empty());
    CHECK_EQ(isec[0], p1);
    CHECK_EQ(isec[1], p2);
    CHECK_EQ(isec.size(), 2);
    CHECK_EQ(std::distance(isec.begin(), isec.end()), 2);

    CHECK(isec.erase(isec.begin() + 1) == isec.end());

    CHECK(!isec.empty());
    CHECK_EQ(isec[0], p1);
    CHECK_EQ(isec.size(), 1);
    CHECK_EQ(std::distance(isec.begin(), isec.end()), 1);
}

// =================================================================================================
TEST_CASE(Intersections_erase_first)
{
    Point p1{1.0, 1.0};
    Point p2{2.0, 2.0};

    Intersections isec(p1, p2);

    CHECK(!isec.empty());
    CHECK_EQ(isec[0], p1);
    CHECK_EQ(isec[1], p2);
    CHECK_EQ(isec.size(), 2);
    CHECK_EQ(std::distance(isec.begin(), isec.end()), 2);

    CHECK(isec.erase(isec.begin()) == isec.begin());

    CHECK(!isec.empty());
    CHECK_EQ(isec[0], p2);
    CHECK_EQ(isec.size(), 1);
    CHECK_EQ(std::distance(isec.begin(), isec.end()), 1);
}
