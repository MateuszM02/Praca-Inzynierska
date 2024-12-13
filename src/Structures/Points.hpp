#pragma once
#include "../Algorithms/Merger.hpp"

using namespace src::Algorithms;

namespace src::Structures
{

struct Point2D
{
private:
    unsigned int x;
    unsigned int y;

public:
    // konstruktor domyslny potrzebny do stworzenia wektora elementow
    Point2D()
    : x{0}
    , y{0}
    { }

    Point2D(const unsigned int first, const unsigned int second)
    : x{first}
    , y{second}
    { }

    // konstruktor/operator przypisania przenoszacego
    Point2D(Point2D&& other);
    Point2D& operator=(const Point2D&& other);

    // konstruktor/operator przypisania kopiujacego
    Point2D(const Point2D& other);
    Point2D& operator=(const Point2D& other);
    
    // operatory potrzebne do scalania/sortowania
    bool operator==(const Point2D& other) const;
    bool operator<(const Point2D& other) const;
};

class Points : public Merger<Point2D>
{
};

} // namespace src::Structures
