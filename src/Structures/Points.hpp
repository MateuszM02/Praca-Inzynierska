#pragma once
#include "../Algorithms/3Merge/Merger.hpp"

using namespace src::Algorithms;

namespace src::Structures
{

struct Point2D
{
    // konstruktor domyslny potrzebny do stworzenia wektora elementow
    Point2D()
    : x{0}
    , y{0}
    { }

    Point2D(const unsigned int first, const unsigned int second)
    : x{first}
    , y{second}
    { }

    unsigned int x;
    unsigned int y;
};

} // namespace src::Structures
