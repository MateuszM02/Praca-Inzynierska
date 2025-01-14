#pragma once

#include "Base.hpp"

#include <boost/range/algorithm/merge.hpp> // boost::range::merge

namespace src::Algorithms
{

template <typename DataType>
struct MergerData final
{
    explicit MergerData(std::vector<DataType>&& vec1, std::vector<DataType>&& vec2)
    : v1_{std::move(vec1)}
    , v2_{std::move(vec2)}
    { }

    std::vector<DataType> v1_;
    std::vector<DataType> v2_;
};

template <typename DataType>
requires std::is_copy_constructible_v<DataType>
class Merger final : public BaseClass<std::vector<DataType>>
{
public:
    explicit Merger(MergerData<DataType>&& data)
    : v1_{std::move(data.v1_)}
    , v2_{std::move(data.v2_)}
    { }

private:
    void resetData() const override { }

    std::vector<DataType> executeSTL() const override
    {
        std::vector<DataType> resultVec;
        resultVec.reserve(v1_.size() + v2_.size());
        std::merge(v1_.begin(), v1_.end(), v2_.begin(), v2_.end(), std::back_inserter(resultVec));
        return resultVec;
    }

    std::vector<DataType> executeBoost() const override
    {
        std::vector<DataType> resultVec;
        resultVec.reserve(v1_.size() + v2_.size());
        boost::range::merge(v1_, v2_, std::back_inserter(resultVec));
        return resultVec;
    }

    std::vector<DataType> executeSimple() const override
    {
        const unsigned int size1 = v1_.size();
        const unsigned int size2 = v2_.size();

        std::vector<DataType> resultVec;
        resultVec.reserve(size1 + size2);
        unsigned int index1 = 0;
        unsigned int index2 = 0;

        while (index1 < size1 && index2 < size2)
        {
            if (v1_[index1] < v2_[index2])
            {
                resultVec.emplace_back(v1_[index1]);
                index1++;
            }
            else
            {
                resultVec.emplace_back(v2_[index2]);
                index2++;
            }
        }
        while (index1 < size1)
        {
            resultVec.emplace_back(v1_[index1]);
            index1++;
        }
        while (index2 < size2)
        {
            resultVec.emplace_back(v2_[index2]);
            index2++;
        }
        return resultVec;
    }

    const std::vector<DataType> v1_;
    const std::vector<DataType> v2_;
};

} // namespace src::Algorithms
