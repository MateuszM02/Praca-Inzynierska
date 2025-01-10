#pragma once

#include "BaseWrapper.hpp"

namespace src::Structures
{

class IntVector final : BaseWrapper<ENABLE_MOVE, ENABLE_COPY>
{
public:
    explicit IntVector(const std::vector<int>& v)
    : BaseWrapper<ENABLE_MOVE, ENABLE_COPY>({ &values_ })
    , values_{std::move(v)}
    { }

    std::size_t size() const noexcept { return values_.size(); }
    int get(const unsigned int index) const { return values_[index]; }

    auto cbegin() const { return values_.cbegin(); }
    auto cend() const { return values_.cend(); }

private:
    std::vector<int> values_;
};

} // namespace src::Structures
