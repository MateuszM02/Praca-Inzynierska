#pragma once

#include "../../Structures/IntVector.hpp"
#include "../../Structures/Points.hpp"

template <typename DataType>
using MergerPtr = std::shared_ptr<Merger<DataType>>;

using namespace src::Structures;

namespace src::Algorithms
{

class MergerImpl final
{
public:
    MergerImpl() = delete;

    static void pointCopyAssignFunc(Point2D& dest, const Point2D& src)
    {
        dest.x = src.x;
        dest.y = src.y;
    }

    static bool pointEqFunc(const Point2D& p1, const Point2D& p2)
    {
        return p1.x == p2.x && p1.y == p2.y;
    }

    static bool pointLessFunc(const Point2D& p1, const Point2D& p2)
    {
        return  p1.x != p2.x ?
                p1.x < p2.x :
                p1.y < p2.y;
    }

    static void intVectorCopyAssignFunc(IntVector& dest, const IntVector& src)
    {
        dest.values = src.values;
    }

    static bool intVectorEqFunc(const IntVector& v1, const IntVector& v2)
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

    static bool intVectorLessFunc(const IntVector& v1, const IntVector& v2)
    {
        return std::lexicographical_compare(
            v1.values.begin(), v1.values.end(), v2.values.begin(), v2.values.end());
    }

};

} // namespace src::Algorithms
