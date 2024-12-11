#include "Points.hpp"

namespace src::Merge::Points1
{

// Konstruktor przenoszacy
Point2D::Point2D(Point2D&& other)
: x{other.x}
, y{other.y}
{ }

// konstruktor kopiujacy
Point2D::Point2D(const Point2D& other)
: x{other.x}
, y{other.y}
{ }

// Operator przenoszacy
Point2D& Point2D::operator=(const Point2D&& other)
{
    if (this != &other)
    {
        this->x = other.x;
        this->y = other.y;
    }
    return *this;
}

// Operator kopiujacy
Point2D& Point2D::operator=(const Point2D& other)
{
    if (this != &other)
    {
        this->x = other.x;
        this->y = other.y;
    }
    return *this;
}

bool Point2D::operator==(const Point2D& other) const
{
    return this->x == other.x && this->y == other.y;
}

bool Point2D::operator<(const Point2D& other) const
{
    return  this->x != other.x ? 
            this->x < other.x :
            this->y < other.y;
}

} // namespace src::Merge::Points1
