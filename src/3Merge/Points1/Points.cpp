#include "Points.hpp"

namespace src::Merge::Points1
{
// Operator rownosci punktow do sprawdzania poprawnosci scalania
bool Point2D::operator==(const Point2D& other) const
{
    return this->x == other.x && this->y == other.y;
}

// Operator mniejszosci punktow potrzebny do scalania
bool Point2D::operator<(const Point2D& other) const
{
    return  this->x != other.x ? 
            this->x < other.x :
            this->y < other.y;
}

} // namespace src::Merge::Points1
