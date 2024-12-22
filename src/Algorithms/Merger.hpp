#pragma once

#include "Base.hpp"
#include "DataWrapper.hpp"

#include <boost/range/algorithm/merge.hpp> // boost::range::merge

namespace src::Algorithms
{

template <typename DataType>
struct MergerData final
{
    using DataVector = std::vector<DataWrapper<DataType>>;

    MergerData(
        DataVector vec1,
        DataVector vec2)
    : v1_{std::move(vec1)}
    , v2_{std::move(vec2)}
    { }

    DataVector v1_;
    DataVector v2_;
};

template <typename DataType>
class Merger final : public BaseClass<DataType, std::vector<DataWrapper<DataType>>>
{

using DataVector = std::vector<DataWrapper<DataType>>;

public:
    Merger(MergerData<DataType> data)
    : v1_(std::move(data.v1_))
    , v2_(std::move(data.v2_))
    { }

private:
    void resetData() override { }

    DataVector executeSTL() override
    {
        DataVector resultVec(v1_.size() + v2_.size(), DataWrapper<DataType>(DataType(), nullptr, nullptr));
        std::merge(v1_.begin(), v1_.end(), v2_.begin(), v2_.end(), resultVec.begin());
        return resultVec;
    }

    DataVector executeBoost() override
    {
        DataVector resultVec(v1_.size() + v2_.size(), DataWrapper<DataType>(DataType(), nullptr, nullptr));
        boost::range::merge(v1_, v2_, resultVec.begin());
        return resultVec;
    }

    DataVector executeSimple() override
    {
        const unsigned int size1 = v1_.size();
        const unsigned int size2 = v2_.size();

        DataVector resultVec(size1 + size2, DataWrapper<DataType>(DataType(), nullptr, nullptr));
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

public:
    DataVector v1_;
    DataVector v2_;
};

} // namespace src::Algorithms
