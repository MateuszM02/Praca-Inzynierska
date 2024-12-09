#pragma once
#include "../Merger.hpp"

// Przyklad 3. Wektory liczb --------------------------------------------------------------------------------

namespace src::Merge::Vector3
{

struct IntVector
{
private:
    std::vector<int> values;
public:
    int at(const unsigned int i) const { return values[i]; }
    size_t size() const { return values.size(); }

    bool operator==(const IntVector& other) const;
    bool operator<(const IntVector& other) const;
};

class MyVector : public Merger<IntVector>
{
};

} // namespace src::Merge::Vector3
