#pragma once

#include "../Concepts/DataTypeConcepts.hpp"
#include "IntVector.hpp"

using namespace src::Concepts;

namespace src::Structures
{

// implementacja operatorow potrzebnych do testow na klasie IntVector
bool operator==(const IntVector& v1, const IntVector& v2)
{
    if (v1.size() != v2.size())
        return false;
    
    for (unsigned int i = 0; i < v1.size(); ++i)
    {
        if (v1.get(i) != v2.get(i))
            return false;
    }
    return true;
}

bool operator!=(const IntVector& v1, const IntVector& v2)
{
    return !(v1 == v2);
}

bool operator<(const IntVector& v1, const IntVector& v2)
{
    return std::lexicographical_compare(
        v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend());
}

bool operator>(const IntVector& v1, const IntVector& v2)
{
    return v2 < v1;
}

std::ostream& operator<<(std::ostream& os, const IntVector& iv) 
{
    os << "[";
    for (size_t i = 0; i < iv.size(); ++i)
    {
        os << iv.get(i) << ", ";
    }
    os << "]";
    return os;
}

} // namespace src::Structures
