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
public:
    Points(const std::vector<Point2D>& v1, const std::vector<Point2D>& v2)
    : Merger(v1, v2)
    { }
};

} // namespace src::Merge::Points1
