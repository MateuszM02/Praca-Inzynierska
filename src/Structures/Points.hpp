#pragma once

#include "BaseWrapper.hpp"

using namespace src::Structures;

namespace src::Structures
{

class Point2D final : BaseWrapper<ENABLE_MOVE, ENABLE_COPY>
{
public:
    // konstruktor domyslny potrzebny do stworzenia wektora elementow
    explicit Point2D()
    : BaseWrapper<ENABLE_MOVE, ENABLE_COPY>({ &x, &y })
    , x{0}
    , y{0}
    { }

    explicit Point2D(const unsigned int first, const unsigned int second)
    : BaseWrapper<ENABLE_MOVE, ENABLE_COPY>({ &x, &y })
    , x{first}
    , y{second}
    { }

    unsigned int x;
    unsigned int y;
};

} // namespace src::Structures
