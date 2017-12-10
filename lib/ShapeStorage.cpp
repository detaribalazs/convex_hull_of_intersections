#include <ShapeStorage.h>
#include <Intersections.h>

#include <iterator>

using namespace gk;

// =================================================================================================
size_t ShapeStorage::size() const
{
    return std::get<0>(shapes).size() + std::get<1>(shapes).size();
}

// =================================================================================================
std::vector<Point> ShapeStorage::intersectAll() const
{
    std::vector<Point> intersections;

    for (const auto& lineSegment: std::get<0>(shapes))
    {
        for (const auto& lineSegment2: std::get<0>(shapes))
        {
            if (lineSegment == lineSegment2)
                continue;

            auto isec = intersect(lineSegment, lineSegment2);
            std::copy(isec.begin(), isec.end(), std::back_inserter(intersections));
        }

        for (const auto& circle: std::get<0>(shapes))
        {
            auto isec = intersect(lineSegment, circle);
            std::copy(isec.begin(), isec.end(), std::back_inserter(intersections));
        }
    }

    for (const auto& circle: std::get<0>(shapes))
    {
        for (const auto& circle2: std::get<0>(shapes))
        {
            if (circle == circle2)
                continue;

            auto isec = intersect(circle, circle2);
            std::copy(isec.begin(), isec.end(), std::back_inserter(intersections));
        }
    }

    return intersections;
}
