#pragma once

#include "Base.hpp"

#include <boost/range/algorithm/sort.hpp> // boost::range::sort

namespace src::Algorithms
{

template <typename DataType>
requires std::is_copy_constructible_v<DataType>
class Sorter final : public BaseClass<std::vector<DataType>>
{
public:
    explicit Sorter(std::vector<DataType>&& elements)
    : initialElements_{elements}
    , sortedElements_{std::move(elements)}
    { }

private:
    void resetData() const override
    {
        sortedElements_ = initialElements_;
    }

    std::vector<DataType> executeSTL() const override
    {
        std::sort(sortedElements_.begin(), sortedElements_.end());
        return sortedElements_;
    }

    std::vector<DataType> executeBoost() const override
    {
        boost::range::sort(sortedElements_);
        return sortedElements_;
    }

    std::vector<DataType> executeSimple() const override
    {
        quicksort(sortedElements_, 0, sortedElements_.size() - 1);
        return sortedElements_;
    }

    void quicksort(std::vector<DataType>& vec, int low, int high) const
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

    int medianOfThreePartition(std::vector<DataType>& vec, int low, int high) const
    {
        int mid = low + (high - low) / 2;
        if (vec[mid] < vec[low])
            std::swap(vec[low], vec[mid]);
        if (vec[high] < vec[low])
            std::swap(vec[low], vec[high]);
        if (vec[high] < vec[mid])
            std::swap(vec[mid], vec[high]);

        std::swap(vec[mid], vec[high]);

        DataType pivot = std::move(vec[high]);
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

    void insertionSort(std::vector<DataType>& vec, int low, int high) const
    {
        for (int i = low + 1; i <= high; ++i)
        {
            DataType key = std::move(vec[i]);
            int j = i - 1;

            while (j >= low && key < vec[j])
            {
                vec[j + 1] = std::move(vec[j]);
                --j;
            }
            vec[j + 1] = std::move(key);
        }
    }

    const std::vector<DataType> initialElements_;
    mutable std::vector<DataType> sortedElements_;
};

} // namespace src::Algorithms
