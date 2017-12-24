#include <Shapes.h>
#include "unit_test.h"
#include <type_traits>

using namespace gk;

// =================================================================================================
namespace
{
    template<typename T>
    struct is_nothrow_movable
    {
        static constexpr bool value =
            std::is_nothrow_move_constructible<T>::value &&
            std::is_nothrow_move_assignable<T>::value;
    };

    template<typename T>
    constexpr bool is_nothrow_movable_v = is_nothrow_movable<T>::value;
}

// =================================================================================================
static_assert(is_nothrow_movable_v<Point>, "nothrow movable Point");
static_assert(is_nothrow_movable_v<Bounds>, "nothrow movable Bounds");
static_assert(is_nothrow_movable_v<BoundsXY>, "nothrow movable BoundsXY");
static_assert(is_nothrow_movable_v<Line>, "nothrow movable Line");
static_assert(is_nothrow_movable_v<LineSegment>, "nothrow movable LineSegment");
static_assert(is_nothrow_movable_v<Circle>, "nothrow movable Circle");
