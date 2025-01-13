#pragma once

#include <limits>
#include <ostream>

#include "Points.hpp"

namespace src::Structures
{

// implementacja operatorow potrzebnych do testow na klasie Point2D
template <typename DataType>
Point2D<DataType> operator+(const Point2D<DataType>& p1, const Point2D<DataType>& p2)
{
    return Point2D(p1.first_ + p2.first_, p1.second_ + p2.second_);
}

template <typename DataType>
Point2D<DataType> operator/(const Point2D<DataType>& p, const unsigned int div)
{
    return Point2D(p.first_ / div, p.second_ / div);
}

template <typename DataType>
Point2D<DataType>& operator+=(Point2D<DataType>& p1, const Point2D<DataType>& p2)
{
    p1.first_ += p2.first_;
    p1.second_ += p2.second_;
    return p1;
}

template <typename DataType>
bool operator==(const Point2D<DataType>& p1, const Point2D<DataType>& p2)
{
    return p1.first_ == p2.first_ && p1.second_ == p2.second_;
}

template <typename DataType>
bool operator!=(const Point2D<DataType>& p1, const Point2D<DataType>& p2)
{
    return !(p1 == p2);
}

template <typename DataType>
bool operator<(const Point2D<DataType>& p1, const Point2D<DataType>& p2)
{
    return  p1.first_ != p2.first_ ?
            p1.first_ < p2.first_ :
            p1.second_ < p2.second_;
}

template <typename DataType>
bool operator>(const Point2D<DataType>& p1, const Point2D<DataType>& p2)
{
    return p2 < p1;
}

template <typename DataType>
std::ostream& operator<<(std::ostream& os, const Point2D<DataType>& p) 
{
    os << "(" << p.first_ << ", " << p.second_ << ")";
    return os;
}

} // namespace src::Structures

namespace std
{

template <typename DataType>
class numeric_limits<src::Structures::Point2D<DataType>>
{
public:
    static const bool is_specialized = true;
    
    static src::Structures::Point2D<DataType> min()
    {
        return src::Structures::Point2D(
            std::numeric_limits<unsigned int>::min(),
            std::numeric_limits<unsigned int>::min());
    }
    
    static src::Structures::Point2D<DataType> max()
    {
        return src::Structures::Point2D(
            std::numeric_limits<unsigned int>::max(),
            std::numeric_limits<unsigned int>::max());
    }
    
    static src::Structures::Point2D<DataType> lowest()
    {
        return src::Structures::Point2D(
            std::numeric_limits<unsigned int>::lowest(),
            std::numeric_limits<unsigned int>::lowest());
    }
    
    static src::Structures::Point2D<DataType> epsilon()
    {
        return src::Structures::Point2D(
            std::numeric_limits<unsigned int>::epsilon(),
            std::numeric_limits<unsigned int>::epsilon());
    }
};

} // namespace std
