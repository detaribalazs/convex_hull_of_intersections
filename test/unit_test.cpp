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
    return std::fabs(a-b) < 1e-5;
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
static void runTestCase(TestCase* tc)
{
    std::cout << "-- test case: " << tc->name << std::endl;
    tc->run();
}

// =================================================================================================
static int run(const TestCases& tests)
{
    std::cout << "running " << tests.size() << " test cases" << std::endl;
    std::for_each(tests.begin(), tests.end(), runTestCase);
    std::cout << "finished running " << tests.size() << " test cases" << std::endl;
    return 0;
}

// =================================================================================================
int test::runTestCases(int argc, char* argv[])
{
    if (argc == 1)
        return run(testCases());

    TestCases filtered;
    for (TestCase* tc : testCases())
    {
        for (int i = 1; i < argc; ++i)
        {
            if (tc->name == argv[i])
            {
                filtered.push_back(tc);
                break;
            }
        }
    }

    return run(filtered);
}
