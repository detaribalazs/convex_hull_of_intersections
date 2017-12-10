#include <InputParser.h>
#include <Shapes.h>

#include <string>
#include <stdexcept>

using namespace gk;

// =================================================================================================
std::istream& gk::operator>> (std::istream& in, InputLine& line)
{
    in >> line.type;
    switch (line.type)
    {
        case 'L':
            return in >> line.nums[0] >> line.nums[1] >> line.nums[2] >> line.nums[3];
        case 'C':
            return in >> line.nums[0] >> line.nums[1] >> line.nums[2];
        default:
            throw std::runtime_error(std::string("bad shape type '") + line.type + '\'');
    }
}

// =================================================================================================
InsertShapeIterator& InsertShapeIterator::operator= (const InputLine& line)
{
    switch (line.type)
    {
        case 'L':
            storage.add(
                    LineSegment{
                        Point{line.nums[0], line.nums[1]},
                        Point{line.nums[2], line.nums[3]}});
            break;
        case 'C':
            storage.add(
                    Circle{
                        Point{line.nums[0], line.nums[1]},
                        line.nums[2]});
            break;
    }
    return *this;
}
