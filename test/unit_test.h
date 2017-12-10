#pragma once

#include <Shapes.h>

#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <string>

namespace test
{
    constexpr auto pos_inf = std::numeric_limits<float>::infinity();
    constexpr auto neg_inf = -pos_inf;
    constexpr auto nan = std::numeric_limits<float>::quiet_NaN();

    int runTestCases(int argc, char* argv[]);

    struct TestCase
    {
        std::string name;

        TestCase(std::string _name);
        TestCase(const TestCase&) = delete;

        virtual ~TestCase();
        virtual void run() = 0;
    };

    template<typename T>
    inline bool equals(const T& a, const T& b)
    { return a == b; }

    bool equals(float a, float b);

    bool equals(const gk::Point& a, const gk::Point& b);
}

#define TEST_CASE(name) \
    struct TestCase_##name: ::test::TestCase \
    { \
        TestCase_##name(): ::test::TestCase(#name) {} \
        void run() override; \
    } tc_##name; \
    void TestCase_##name::run()

#define IGNORE_TEST_CASE(name) \
    struct TestCase_##name: ::test::TestCase \
    { \
        TestCase_##name(): ::test::TestCase(#name) {} \
        void run() override; \
    }; \
    void TestCase_##name::run()

#define CHECK(expr) \
    do { \
        std::cout << "checking " << #expr << std::endl; \
        assert(expr); \
    } while (0)

#define CHECK_EQ(expr1, expr2) \
    do { \
        std::cout << "checking " << #expr1 << " == " << #expr2 << std::endl; \
        if (!::test::equals(expr1, expr2)) \
            std::cout << "  failed: " << (expr1) << " != " << (expr2) << std::endl; \
        assert(::test::equals(expr1, expr2)); \
    } while (0)
