#pragma once
#include <Intersections.h>
#include <Shapes.h>

#include <algorithm>
#include <tuple>
#include <vector>

namespace gk
{
    template <typename... ShapeTypes>
    class ShapeStorageImpl
    {
        inline static const auto indices = std::make_index_sequence<sizeof...(ShapeTypes)>();

        public:
            template<typename TShape>
            void add(TShape&& shape)
            {
                std::get<std::vector<TShape>>(shapes).push_back(std::forward<TShape>(shape));
            }

            size_t size() const
            {
                return size_impl(indices);
            }

            std::vector<Point> intersect_all() const
            {
                std::vector<Point> intersections = intersect_all(indices);
                std::sort(intersections.begin(), intersections.end());
                auto end = std::unique(intersections.begin(), intersections.end());
                intersections.resize(std::distance(intersections.begin(), end));
                return intersections;
            }

        private:
            template<size_t... idx>
            size_t size_impl(std::index_sequence<idx...>) const
            {
                return (std::get<idx>(shapes).size() + ...);
            }

            template <typename Shape, typename OtherShapes>
            static void intersect_single(
                    std::vector<Point>& result,
                    const Shape& shape,
                    const OtherShapes& otherShapes)
            {
                using namespace std;
                for (auto iter = begin(otherShapes); iter != end(otherShapes); ++iter)
                {
                    auto isec = intersect(shape, *iter);
                    std::copy(isec.begin(), isec.end(), std::back_inserter(result));
                }
            }

            template <typename Head, typename... Rest>
            static void intersect_all(
                    std::vector<Point>& result,
                    const Head& head, const Rest&... rest)
            {
                using namespace std;
                for (auto iter1 = begin(head); iter1 != end(head); ++iter1)
                {
                    for (auto iter2 = std::next(iter1); iter2 != end(head); ++iter2)
                    {
                        auto isec = intersect(*iter1, *iter2);
                        std::copy(isec.begin(), isec.end(), std::back_inserter(result));
                    }

                    (intersect_single(result, *iter1, rest), ...);
                }

                if constexpr(sizeof...(rest) > 0)
                    intersect_all(result, rest...);
            }

            template <size_t... idx>
            std::vector<Point> intersect_all(std::index_sequence<idx...>) const
            {
                std::vector<Point> result;
                intersect_all(result, std::get<idx>(shapes)...);
                return result;
            }

            std::tuple<std::vector<ShapeTypes>...> shapes;
    };

    using ShapeStorage = ShapeStorageImpl<LineSegment, Circle>;
}
