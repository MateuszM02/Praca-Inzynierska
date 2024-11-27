#pragma once
#include "../Merger.hpp"

// Przyklad 1. Para wartosci --------------------------------------------------------------------------------

namespace src::Merge::Points1
{

struct Point2D
{
    int x;
    int y;
};

class Points : public Merger<Point2D>
{
public:
    Points() { }

    bool operator()(const Point2D& elem1, const Point2D& elem2) override;
};
} // namespace src::Merge::Points1
