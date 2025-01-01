#pragma once

#include <limits>

#include "Points.hpp"

namespace src::Structures
{

// implementacja operatorow potrzebnych do testow na klasie Point2D
Point2D operator+(const Point2D& p1, const Point2D& p2)
{
    return { p1.x + p2.x, p1.y + p2.y };
}

Point2D operator/(const Point2D& p, const unsigned int div)
{
    return { p.x / div, p.y / div };
}

Point2D& operator+=(Point2D& p1, const Point2D& p2)
{
    p1.x += p2.x;
    p1.y += p2.y;
    return p1;
}

bool operator==(const Point2D& p1, const Point2D& p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}

bool operator<(const Point2D& p1, const Point2D& p2)
{
    return  p1.x != p2.x ?
            p1.x < p2.x :
            p1.y < p2.y;
}

bool operator>(const Point2D& p1, const Point2D& p2)
{
    return p2 < p1;
}

} // namespace src::Structures

namespace std
{

template <>
class numeric_limits<src::Structures::Point2D>
{
public:
    static const bool is_specialized = true;
    
    static src::Structures::Point2D min()
    {
        return src::Structures::Point2D(
            std::numeric_limits<unsigned int>::min(),
            std::numeric_limits<unsigned int>::min());
    }
    
    static src::Structures::Point2D max()
    {
        return src::Structures::Point2D(
            std::numeric_limits<unsigned int>::max(),
            std::numeric_limits<unsigned int>::max());
    }
    
    static src::Structures::Point2D lowest()
    {
        return src::Structures::Point2D(
            std::numeric_limits<unsigned int>::lowest(),
            std::numeric_limits<unsigned int>::lowest());
    }
    
    static src::Structures::Point2D epsilon()
    {
        return src::Structures::Point2D(
            std::numeric_limits<unsigned int>::epsilon(),
            std::numeric_limits<unsigned int>::epsilon());
    }
};

} // namespace std
