#pragma once

#include "Base.hpp"
#include "../Wrappers/ComparableWrapper.hpp"

#include <boost/range/algorithm/sort.hpp> // boost::range::sort

using namespace src::Wrappers;

namespace src::Algorithms
{

template <typename DataType>
class Sorter final : public BaseClass<DataType, std::vector<ComparableWrapper<DataType>>>
{

using DataVector = std::vector<ComparableWrapper<DataType>>;

public:
    Sorter(DataVector elements)
    : initialElements_(elements)
    , sortedElements_(std::move(elements))
    { }

private:
    void resetData() override
    {
        sortedElements_ = initialElements_;
    }

    DataVector executeSTL() override
    {
        std::sort(sortedElements_.begin(), sortedElements_.end());
        return sortedElements_;
    }

    DataVector executeBoost() override
    {
        boost::range::sort(sortedElements_);
        return sortedElements_;
    }

    DataVector executeSimple() override
    {
        quicksort(sortedElements_, 0, sortedElements_.size() - 1);
        return sortedElements_;
    }
    
    void quicksort(DataVector& vec, int low, int high)
    {
        if (low < high)
        {
            if (high - low < 15)
            {
                insertionSort(vec, low, high);
            }
            else
            {
                int pivot = medianOfThreePartition(vec, low, high);
                quicksort(vec, low, pivot - 1);
                quicksort(vec, pivot + 1, high);
            }
        }
    }
    
    int medianOfThreePartition(DataVector& vec, int low, int high)
    {
        int mid = low + (high - low) / 2;
        if (vec[mid] < vec[low])
            std::swap(vec[low], vec[mid]);
        if (vec[high] < vec[low])
            std::swap(vec[low], vec[high]);
        if (vec[high] < vec[mid])
            std::swap(vec[mid], vec[high]);

        std::swap(vec[mid], vec[high]);

        ComparableWrapper<DataType> pivot = std::move(vec[high]);
        int i = low - 1;
        
        for (int j = low; j < high; ++j)
        {
            if (vec[j] < pivot)
            {
                ++i;
                std::swap(vec[i], vec[j]);
            }
        }
        vec[high] = std::move(pivot);
        std::swap(vec[i + 1], vec[high]);
        return i + 1;
    }

    void insertionSort(DataVector& vec, int low, int high)
    {
        for (int i = low + 1; i <= high; ++i)
        {
            ComparableWrapper<DataType> key = std::move(vec[i]);
            int j = i - 1;

            while (j >= low && key < vec[j])
            {
                vec[j + 1] = std::move(vec[j]);
                --j;
            }
            vec[j + 1] = std::move(key);
        }
    }

public:
    DataVector initialElements_;
    DataVector sortedElements_;
};

} // namespace src::Algorithms
