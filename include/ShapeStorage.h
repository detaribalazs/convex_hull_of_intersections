#pragma once
#include <Shapes.h>

#include <tuple>
#include <vector>

namespace gk
{
    class ShapeStorage
    {
        public:
            template<typename TShape>
            void add(TShape&& shape)
            {
                std::get<std::vector<TShape>>(shapes).push_back(std::forward<TShape>(shape));
            }

            size_t size() const;

            std::vector<Point> intersect_all() const;

        private:
            std::tuple<std::vector<LineSegment>, std::vector<Circle>> shapes;
    };
}
