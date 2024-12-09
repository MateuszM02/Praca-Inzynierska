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
public:
    MyVector(const std::vector<IntVector>& v1, const std::vector<IntVector>& v2)
    : Merger(v1, v2)
    { }
};

} // namespace src::Merge::Vector3
