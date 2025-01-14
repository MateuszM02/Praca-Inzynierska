#pragma once

#include <limits>
#include <ostream>

#include "../Concepts/DataTypeConcepts.hpp"
#include "CustomPair.hpp"

using namespace src::Concepts;

namespace src::Structures
{

// implementacja operatorow potrzebnych do testow na klasie CustomPair
template <typename DataType, bool MoveEnabled, bool CopyEnabled>
CustomPair<DataType, MoveEnabled, CopyEnabled> operator+(
    const CustomPair<DataType, MoveEnabled, CopyEnabled>& p1,
    const CustomPair<DataType, MoveEnabled, CopyEnabled>& p2)
{
    return CustomPair<DataType, MoveEnabled, CopyEnabled>(p1.first_ + p2.first_, p1.second_ + p2.second_);
}

template <typename DataType, bool MoveEnabled, bool CopyEnabled>
CustomPair<DataType, MoveEnabled, CopyEnabled> operator/(
    const CustomPair<DataType, MoveEnabled, CopyEnabled>& p,
    const unsigned int div)
{
    return CustomPair<DataType, MoveEnabled, CopyEnabled>(p.first_ / div, p.second_ / div);
}

template <typename DataType, bool MoveEnabled, bool CopyEnabled>
CustomPair<DataType, MoveEnabled, CopyEnabled>& operator+=(
    CustomPair<DataType, MoveEnabled, CopyEnabled>& p1,
    const CustomPair<DataType, MoveEnabled, CopyEnabled>& p2)
{
    p1.first_ += p2.first_;
    p1.second_ += p2.second_;
    return p1;
}

template <typename DataType, bool MoveEnabled, bool CopyEnabled>
bool operator==(
    const CustomPair<DataType, MoveEnabled, CopyEnabled>& p1,
    const CustomPair<DataType, MoveEnabled, CopyEnabled>& p2)
{
    return p1.first_ == p2.first_ && p1.second_ == p2.second_;
}

template <typename DataType, bool MoveEnabled, bool CopyEnabled>
bool operator!=(
    const CustomPair<DataType, MoveEnabled, CopyEnabled>& p1,
    const CustomPair<DataType, MoveEnabled, CopyEnabled>& p2)
{
    return !(p1 == p2);
}

template <typename DataType, bool MoveEnabled, bool CopyEnabled>
bool operator<(
    const CustomPair<DataType, MoveEnabled, CopyEnabled>& p1,
    const CustomPair<DataType, MoveEnabled, CopyEnabled>& p2)
{
    return  p1.first_ != p2.first_ ?
            p1.first_ < p2.first_ :
            p1.second_ < p2.second_;
}

template <typename DataType, bool MoveEnabled, bool CopyEnabled>
bool operator>(
    const CustomPair<DataType, MoveEnabled, CopyEnabled>& p1,
    const CustomPair<DataType, MoveEnabled, CopyEnabled>& p2)
{
    return p2 < p1;
}

template <typename DataType, bool MoveEnabled, bool CopyEnabled>
std::ostream& operator<<(std::ostream& os,
    const CustomPair<DataType, MoveEnabled, CopyEnabled>& p) 
{
    os << "(" << p.first_ << ", " << p.second_ << ")";
    return os;
}

} // namespace src::Structures

namespace std
{

template <HasNumericLimits DataType, bool MoveEnabled, bool CopyEnabled>
class numeric_limits<src::Structures::CustomPair<DataType, MoveEnabled, CopyEnabled>>
{
public:
    static const bool is_specialized = true;
    
    static src::Structures::CustomPair<DataType, MoveEnabled, CopyEnabled> min()
    {
        return src::Structures::CustomPair<DataType, MoveEnabled, CopyEnabled>(
            std::numeric_limits<DataType>::min(),
            std::numeric_limits<DataType>::min());
    }
    
    static src::Structures::CustomPair<DataType, MoveEnabled, CopyEnabled> max()
    {
        return src::Structures::CustomPair<DataType, MoveEnabled, CopyEnabled>(
            std::numeric_limits<DataType>::max(),
            std::numeric_limits<DataType>::max());
    }
    
    static src::Structures::CustomPair<DataType, MoveEnabled, CopyEnabled> lowest()
    {
        return src::Structures::CustomPair<DataType, MoveEnabled, CopyEnabled>(
            std::numeric_limits<DataType>::lowest(),
            std::numeric_limits<DataType>::lowest());
    }
    
    static src::Structures::CustomPair<DataType, MoveEnabled, CopyEnabled> epsilon()
    {
        return src::Structures::CustomPair<DataType, MoveEnabled, CopyEnabled>(
            std::numeric_limits<DataType>::epsilon(),
            std::numeric_limits<DataType>::epsilon());
    }
};

} // namespace std
