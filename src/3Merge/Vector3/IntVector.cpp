#include "IntVector.hpp"

namespace src::Merge::Vector3
{
// v1 jest "mniejszym" wektorem od v2 kiedy:
// 1. ma mniej elementow LUB
// 2. jest wiecej indeksow i dla ktorych v1[i] < v2[i] niz j dla ktorych v1[j] > v2[j]
bool IntVector::operator()(const std::vector<int>& v1, const std::vector<int>& v2)
{
    if (v1.size() != v2.size())
        return v1.size() < v2.size();
    
    unsigned int v1Smaller = 0;
    unsigned int v1Bigger = 0;
    
    for (unsigned int i = 0; i < v1.size(); i++)
    {
        if (v1[i] < v2[i])
            v1Smaller++;
        else if (v1[i] > v2[i])
            v1Bigger++;
    }
    return v1Smaller < v1Bigger;
}
} // namespace src::Merge::Vector3
