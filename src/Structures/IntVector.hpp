#pragma once

#include "BaseWrapper.hpp"

namespace src::Structures
{

class IntVector final : BaseWrapper<DISABLE_MOVE, DISABLE_COPY>
{
public:
    // konstruktor domyslny potrzebny do stworzenia wektora elementow
    IntVector()
    : BaseWrapper<DISABLE_MOVE, DISABLE_COPY>({ &values_ })
    , values_{{}}
    { }

    IntVector(std::vector<int> v)
    : BaseWrapper<DISABLE_MOVE, DISABLE_COPY>({ &values_ })
    , values_{std::move(v)}
    { }

    std::size_t size() const { return values_.size(); }
    int at(const unsigned int index) const { return values_[index]; }

    auto cbegin() const { return values_.cbegin(); }
    auto cend() const { return values_.cend(); }

private:
    std::vector<int> values_;
};

} // namespace src::Structures
