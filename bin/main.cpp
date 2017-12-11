#include <InputParser.h>
#include <ShapeStorage.h>
#include <OutputWriter.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>

int main()
{
    unsigned numShapes;
    std::cin >> numShapes;

    gk::ShapeStorage shapes;
    std::copy(
            std::istream_iterator<gk::InputLine>(std::cin),
            std::istream_iterator<gk::InputLine>(),
            gk::InsertShapeIterator(shapes));

    std::cerr << "Loaded " << shapes.size() << " shapes\n";
    assert(shapes.size() == numShapes);

    auto intersections = shapes.intersectAll();
    std::cerr << "Found " << intersections.size() << " intersections\n";

    std::cout << intersections.size() << '\n';
    std::copy(
            intersections.begin(),
            intersections.end(),
            gk::OutputPointsIterator(std::cout));

    return 0;
}
