#pragma once

#include "IntVector.hpp"

namespace src::Structures
{

// klasa implementujaca operatory potrzebne do testow na klasie IntVector
class IntVectorImpl final
{
public:
    IntVectorImpl() = delete;

    static void copyAssign(IntVector& dest, const IntVector& src)
    {
        dest.values = src.values;
    }

    static bool equal(const IntVector& v1, const IntVector& v2)
    {
        if (v1.values.size() != v2.values.size())
            return false;
        
        for (unsigned int i = 0; i < v1.values.size(); ++i)
        {
            if (v1.values[i] != v2.values[i])
                return false;
        }
        return true;
    }

    static bool less(const IntVector& v1, const IntVector& v2)
    {
        return std::lexicographical_compare(
            v1.values.begin(), v1.values.end(), v2.values.begin(), v2.values.end());
    }
};

} // namespace src::Structures
