#pragma once

#include <ShapeStorage.h>

#include <istream>
#include <iterator>


namespace gk
{
    // represents a parsed input line
    struct InputLine
    {
        char type;
        float nums[4];
    };

    std::istream& operator>> (std::istream& in, InputLine& line);

    // an output iterator to insert shapes into the storage
    class InsertShapeIterator
        : public std::iterator<
            std::output_iterator_tag,
            InputLine, // value_type
            std::ptrdiff_t, // difference_type
            InsertShapeIterator*, // pointer
            InsertShapeIterator& > // reference
    {
        public:
            InsertShapeIterator(ShapeStorage& storage)
                : storage(storage)
            {}

            InsertShapeIterator& operator* ()    { return *this; }
            InsertShapeIterator& operator++()    { return *this; }
            InsertShapeIterator& operator++(int) { return *this; }
            InsertShapeIterator& operator= (const InputLine& line);

        private:
            ShapeStorage& storage;
    };
}
