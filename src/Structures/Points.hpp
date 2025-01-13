#pragma once

#include "BaseWrapper.hpp"

using namespace src::Structures;

namespace src::Structures
{

template <typename DataType = unsigned int>
class Point2D final : BaseWrapper<ENABLE_MOVE, ENABLE_COPY>
{
public:
    using value_type = DataType;

    // potrzebne do 2Accumulate
    explicit Point2D()
    : BaseWrapper<ENABLE_MOVE, ENABLE_COPY>({ &first_, &second_ })
    , first_{0}
    , second_{0}
    { }

    explicit Point2D(const DataType first, const DataType second)
    : BaseWrapper<ENABLE_MOVE, ENABLE_COPY>({ &first_, &second_ })
    , first_{first}
    , second_{second}
    { }

    DataType first_;
    DataType second_;
};

} // namespace src::Structures
