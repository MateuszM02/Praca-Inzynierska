#include "Points.hpp"

namespace src::Merge::Points1
{
bool Points::operator()(const Point2D& elem1, const Point2D& elem2)
{
    return elem1.x + elem2.y < elem2.x + elem2.y;
}
} // namespace src::Merge::Points1
