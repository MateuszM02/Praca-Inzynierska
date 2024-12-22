#pragma once
#include "../Algorithms/Merger.hpp"

namespace src::Structures
{

struct IntVector
{
public:
    // konstruktor domyslny potrzebny do stworzenia wektora elementow
    IntVector()
    : values_{{}}
    { }

    IntVector(std::vector<int> v)
    : values_{std::move(v)}
    { }

    std::size_t size() const { return values_.size(); }
    int at(const unsigned int index) const { return values_[index]; }

    auto cbegin() const { return values_.cbegin(); }
    auto cend() const { return values_.cend(); }

private:
    std::vector<int> values_;
};

} // namespace src::Structures
