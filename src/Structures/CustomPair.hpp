#pragma once

#include "BaseWrapper.hpp"

using namespace src::Structures;

namespace src::Structures
{

template <typename DataType, bool MoveEnabled, bool CopyEnabled>
class CustomPair final : BaseWrapper<MoveEnabled, CopyEnabled>
{
public:
    using value_type = DataType;

    // potrzebne do 2Accumulate
    explicit CustomPair()
    requires std::is_default_constructible_v<DataType>
    : BaseWrapper<MoveEnabled, CopyEnabled>({ &first_, &second_ })
    , first_{DataType()}
    , second_{DataType()}
    { }

    // dla malych struktur
    explicit CustomPair(const DataType& first, const DataType& second)
    requires std::is_copy_constructible_v<DataType>
    : BaseWrapper<MoveEnabled, CopyEnabled>({ &first_, &second_ })
    , first_{first}
    , second_{second}
    { }

    // dla duzych struktur
    explicit CustomPair(DataType&& first, DataType&& second)
    : BaseWrapper<MoveEnabled, CopyEnabled>({ &first_, &second_ })
    , first_{std::move(first)}
    , second_{std::move(second)}
    { }

    DataType first_;
    DataType second_;
};

template <typename DataType>
using CopyablePair = CustomPair<DataType, ENABLE_MOVE, ENABLE_COPY>;

using CopyableUIntPair = CustomPair<unsigned int, ENABLE_MOVE, ENABLE_COPY>;

} // namespace src::Structures
