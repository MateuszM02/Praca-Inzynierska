#pragma once

#include "BaseWrapper.hpp"

namespace src::Structures
{

template <bool MoveEnabled, bool CopyEnabled>
class IntVector final : BaseWrapper<MoveEnabled, CopyEnabled>
{
public:
    explicit IntVector(const std::vector<int>& v)
    : BaseWrapper<MoveEnabled, CopyEnabled>({ &values_ })
    , values_{std::move(v)}
    { }

    std::size_t size() const noexcept { return values_.size(); }
    int get(const unsigned int index) const { return values_[index]; }

    auto cbegin() const { return values_.cbegin(); }
    auto cend() const { return values_.cend(); }

private:
    std::vector<int> values_;
};

using CopyableIntVector = IntVector<ENABLE_MOVE, ENABLE_COPY>;
using NonCopyableIntVector = IntVector<ENABLE_MOVE, DISABLE_COPY>;

} // namespace src::Structures
