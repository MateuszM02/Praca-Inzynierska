#pragma once
#include "../Merger.hpp"

// Przyklad 2. Wektory liczb --------------------------------------------------------------------------------

namespace src::Merge::Vector2
{

class IntVector : public Merger<std::vector<int>>
{
public:
    bool operator()(const std::vector<int>& v1, const std::vector<int>& v2) override;
};
} // namespace src::Merge::Vector2
