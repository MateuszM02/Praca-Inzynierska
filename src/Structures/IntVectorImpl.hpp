#pragma once

#include "IntVector.hpp"

namespace src::Structures
{

// klasa implementujaca operatory potrzebne do testow na klasie IntVector
class IntVectorImpl final
{
public:
    IntVectorImpl() = delete;

    static bool equal(const IntVector& v1, const IntVector& v2)
    {
        if (v1.size() != v2.size())
            return false;
        
        for (unsigned int i = 0; i < v1.size(); ++i)
        {
            if (v1.at(i) != v2.at(i))
                return false;
        }
        return true;
    }

    static bool less(const IntVector& v1, const IntVector& v2)
    {
        return std::lexicographical_compare(
            v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend());
    }
};

} // namespace src::Structures
