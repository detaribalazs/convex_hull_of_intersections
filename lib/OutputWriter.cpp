#include <OutputWriter.h>

#include <iomanip>

using namespace gk;


OutputPointsIterator& OutputPointsIterator::operator= (const Point& point)
{
    out << std::fixed << std::setprecision(4) << point.x << ' ' << point.y << '\n';
    return *this;
}
