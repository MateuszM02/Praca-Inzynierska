#pragma once

#include "Base.hpp"
#include "../Wrappers/ComparableWrapper.hpp"

#include <boost/range/algorithm/merge.hpp> // boost::range::merge

using namespace src::Wrappers;

namespace src::Algorithms
{

template <typename DataType>
struct MergerData final
{
    using DataVector = std::vector<ComparableWrapper<DataType>>;

    MergerData(
        DataVector vec1,
        DataVector vec2)
    : v1_{std::move(vec1)}
    , v2_{std::move(vec2)}
    { }

    const DataVector v1_;
    const DataVector v2_;
};

template <typename DataType>
class Merger final : public BaseClass<DataType, std::vector<ComparableWrapper<DataType>>>
{

using DataVector = std::vector<ComparableWrapper<DataType>>;

public:
    Merger(MergerData<DataType> data)
    : v1_(std::move(data.v1_))
    , v2_(std::move(data.v2_))
    { }

private:
    void resetData() override { }

    DataVector executeSTL() override
    {
        DataVector resultVec(v1_.size() + v2_.size(), ComparableWrapper<DataType>(DataType(), nullptr, nullptr));
        std::merge(v1_.begin(), v1_.end(), v2_.begin(), v2_.end(), resultVec.begin());
        return resultVec;
    }

    DataVector executeBoost() override
    {
        DataVector resultVec(v1_.size() + v2_.size(), ComparableWrapper<DataType>(DataType(), nullptr, nullptr));
        boost::range::merge(v1_, v2_, resultVec.begin());
        return resultVec;
    }

    DataVector executeSimple() override
    {
        const unsigned int size1 = v1_.size();
        const unsigned int size2 = v2_.size();

        DataVector resultVec(size1 + size2, ComparableWrapper<DataType>(DataType(), nullptr, nullptr));
        unsigned int index1 = 0;
        unsigned int index2 = 0;

        while (index1 < size1 && index2 < size2)
        {
            if (v1_[index1] < v2_[index2])
            {
                resultVec[index1+index2] = v1_[index1];
                index1++;
            }
            else
            {
                resultVec[index1+index2] = v2_[index2];
                index2++;
            }
        }
        while (index1 < size1)
        {
            resultVec[index1+index2] = v1_[index1];
            index1++;
        }
        while (index2 < size2)
        {
            resultVec[index1+index2] = v2_[index2];
            index2++;
        }
        return resultVec;
    }

    const DataVector v1_;
    const DataVector v2_;
};

} // namespace src::Algorithms
