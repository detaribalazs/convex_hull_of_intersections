#pragma once

#include <Shapes.h>
#include <iterator>
#include <ostream>

namespace gk
{
    class OutputPointsIterator
        : public std::iterator<
            std::output_iterator_tag,
            Point, // value_type
            std::ptrdiff_t, // difference_type
            OutputPointsIterator*, // pointer
            OutputPointsIterator& > // reference
    {
        public:
            OutputPointsIterator(std::ostream& out)
                : out(out)
            {}

            OutputPointsIterator& operator* ()    { return *this; }
            OutputPointsIterator& operator++()    { return *this; }
            OutputPointsIterator& operator++(int) { return *this; }
            OutputPointsIterator& operator= (const Point& point);

        private:
            std::ostream& out;
    };
}
