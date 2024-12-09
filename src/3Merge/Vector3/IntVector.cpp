#include "IntVector.hpp"

namespace src::Merge::Vector3
{
bool IntVector::operator==(const IntVector& other) const
{
    if (this->size() != other.size())
        return this->size() < other.size();
    
    for (unsigned int i = 0; i < this->size(); i++)
    {
        if (this->at(i) != other.at(i))
            return false;
    }
    
    return true;
}

// this jest "mniejszym" wektorem od other kiedy:
// 1. ma mniej elementow LUB
// 2. jest wiecej indeksow i dla ktorych this[i] < other[i] niz j dla ktorych this[j] > other[j]
bool IntVector::operator<(const IntVector& other) const
{
    if (this->size() != other.size())
        return this->size() < other.size();
    
    unsigned int v1Smaller = 0;
    unsigned int v1Bigger = 0;
    
    for (unsigned int i = 0; i < this->size(); i++)
    {
        if (this->at(i) < other.at(i))
            v1Smaller++;
        else if (this->at(i) > other.at(i))
            v1Bigger++;
    }
    return v1Smaller < v1Bigger;
}

} // namespace src::Merge::Vector3
