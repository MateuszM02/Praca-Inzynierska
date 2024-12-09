#pragma once
#include "../Merger.hpp"

// Przyklad 1. Para wartosci --------------------------------------------------------------------------------

namespace src::Merge::Points1
{

struct Point2D
{
    int x;
    int y;

    bool operator==(const Point2D& other) const;
    bool operator<(const Point2D& other) const;
};

class Points : public Merger<Point2D>
{
};

} // namespace src::Merge::Points1
