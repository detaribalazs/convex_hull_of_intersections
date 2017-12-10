#include <InputParser.h>
#include <ShapeStorage.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>

int main()
{
    unsigned numShapes;
    std::cin >> numShapes;

    gk::ShapeStorage store;
    std::copy(
            std::istream_iterator<gk::InputLine>(std::cin),
            std::istream_iterator<gk::InputLine>(),
            gk::InsertShapeIterator(store));

    std::cerr << "Loaded " << store.size() << " shapes\n";

    assert(store.size() == numShapes);

    return 0;
}
