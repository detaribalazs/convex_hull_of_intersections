#include <ShapeStorage.h>
#include <Intersections.h>

#include <algorithm>
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

    auto linesBegin = std::get<0>(shapes).cbegin();
    auto linesEnd = std::get<0>(shapes).cend();
    auto circlesBegin = std::get<1>(shapes).cbegin();
    auto circlesEnd = std::get<1>(shapes).cend();

    for (auto line1 = linesBegin; line1 != linesEnd; ++line1)
    {
        for (auto line2 = std::next(line1); line2 != linesEnd; ++line2)
        {
            auto isec = intersect(*line1, *line2);
            std::copy(isec.begin(), isec.end(), std::back_inserter(intersections));
        }

        for (auto circle = circlesBegin; circle != circlesEnd; ++circle)
        {
            auto isec = intersect(*line1, *circle);
            std::copy(isec.begin(), isec.end(), std::back_inserter(intersections));
        }
    }

    for (auto circle1 = circlesBegin; circle1 != circlesEnd; ++circle1)
    {
        for (auto circle2 = std::next(circle1); circle2 != circlesEnd; ++circle2)
        {
            auto isec = intersect(*circle1, *circle2);
            std::copy(isec.begin(), isec.end(), std::back_inserter(intersections));
        }
    }

    std::sort(intersections.begin(), intersections.end());
    auto end = std::unique(intersections.begin(), intersections.end());
    intersections.resize(std::distance(intersections.begin(), end));

    return intersections;
}
