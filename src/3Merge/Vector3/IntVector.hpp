#pragma once
#include "../Merger.hpp"

// Przyklad 3. Wektory liczb --------------------------------------------------------------------------------

namespace src::Merge::Vector3
{

class IntVector : public Merger<std::vector<int>>
{
public:
    IntVector() { }

    bool operator()(const std::vector<int>& v1, const std::vector<int>& v2) override;
};
} // namespace src::Merge::Vector3
