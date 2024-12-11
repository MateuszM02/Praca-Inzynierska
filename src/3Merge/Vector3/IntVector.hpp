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
    // konstruktor domyslny potrzebny do stworzenia wektora elementow
    IntVector()
    : values{{}}
    { }

    IntVector(const std::vector<int>& v)
    : values{std::move(v)}
    { }

    int at(const unsigned int i) const { return values[i]; }
    size_t size() const { return values.size(); }

    // konstruktor/operator przypisania przenoszacego
    IntVector(IntVector&& other);
    IntVector& operator=(const IntVector&& other);

    // konstruktor/operator przypisania kopiujacego
    IntVector(const IntVector& other);
    IntVector& operator=(const IntVector& other);
    
    // operatory potrzebne do scalania/sortowania
    bool operator==(const IntVector& other) const;
    bool operator<(const IntVector& other) const;
};

class MyVector : public Merger<IntVector>
{
};

} // namespace src::Merge::Vector3
