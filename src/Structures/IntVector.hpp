#pragma once
#include "../Algorithms/Merger.hpp"

using namespace src::Algorithms;

namespace src::Structures
{

struct IntVector
{
    // konstruktor domyslny potrzebny do stworzenia wektora elementow
    IntVector()
    : values{{}}
    { }

    IntVector(const std::vector<int>& v)
    : values{std::move(v)}
    { }

    std::vector<int> values;
};

} // namespace src::Structures
