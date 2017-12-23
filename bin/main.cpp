#include <ConvexHull.h>
#include <InputParser.h>
#include <OutputWriter.h>
#include <PolygonArea.h>
#include <ShapeStorage.h>

#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <iterator>

// =================================================================================================
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

    auto intersections = shapes.intersect_all();
    std::cerr << "Found " << intersections.size() << " intersections\n";

    std::cout << intersections.size() << '\n';
    std::copy(
            intersections.begin(),
            intersections.end(),
            gk::OutputPointsIterator(std::cout));

    auto hull = gk::convex_hull(std::move(intersections));
    std::cerr << "Found " << hull.size() << " convex hull points\n";

    std::cout << hull.size() << '\n';
    std::copy(hull.begin(), hull.end(), gk::OutputPointsIterator(std::cout));

    auto area = gk::convex_area(std::move(hull));
    std::cerr << "Area of the convex hull: " << std::fixed << std::setprecision(4) << area << '\n';
    std::cout << std::fixed << std::setprecision(4) << area << '\n';

    return 0;
}
