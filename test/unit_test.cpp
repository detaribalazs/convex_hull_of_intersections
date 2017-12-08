#include "unit_test.h"

#include <algorithm>
#include <vector>

using namespace test;

using TestCases = std::vector<TestCase*>;

// =================================================================================================
bool test::equals(float a, float b)
{
    if (a == b)
        return true;
    return std::fabs(a-b) < 1e-6;
}

// =================================================================================================
bool test::equals(const gk::Point& a, const gk::Point& b)
{
    return equals(a.x, b.x) && equals(a.y, b.y);
}

// =================================================================================================
static TestCases& testCases()
{
    static TestCases tests;
    return tests;
}

// =================================================================================================
TestCase::TestCase(std::string _name)
    : name(std::move(_name))
{
    testCases().push_back(this);
}

// =================================================================================================
TestCase::~TestCase()
{
    auto found = std::find(testCases().begin(), testCases().end(), this);
    assert(found != testCases().end());
    testCases().erase(found);
}

// =================================================================================================
static void run(TestCase* tc)
{
    std::cout << "-- test case: " << tc->name << std::endl;
    tc->run();
}

// =================================================================================================
int test::runTestCases()
{
    std::cout << "running " << testCases().size() << " test cases" << std::endl;
    std::for_each(testCases().begin(), testCases().end(), run);
    std::cout << "finished running " << testCases().size() << " test cases" << std::endl;
    return 0;
}
