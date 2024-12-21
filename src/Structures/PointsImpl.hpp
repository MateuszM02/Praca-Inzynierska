#pragma once

#include "Points.hpp"

namespace src::Structures
{

// klasa implementujaca operatory potrzebne do testow na klasie Point2D
class Point2DImpl final
{
public:
    Point2DImpl() = delete;

    static void copyAssign(Point2D& dest, const Point2D& src)
    {
        dest.x = src.x;
        dest.y = src.y;
    }

    static void moveAssign(Point2D& dest, Point2D&& src)
    {
        dest.x = src.x;
        dest.y = src.y;
    }

    static bool equal(const Point2D& p1, const Point2D& p2)
    {
        return p1.x == p2.x && p1.y == p2.y;
    }

    static bool less(const Point2D& p1, const Point2D& p2)
    {
        return  p1.x != p2.x ?
                p1.x < p2.x :
                p1.y < p2.y;
    }
};

} // namespace src::Structures
