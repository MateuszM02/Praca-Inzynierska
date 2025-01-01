#pragma once

#include "Base.hpp"
#include "../Concepts/ContainerConcepts.hpp"

#include <boost/range/algorithm/nth_element.hpp> // boost::range::nth_element

using namespace src::Concepts;

namespace src::Algorithms
{

template <typename DataType, NthElementCompatible Container = std::vector<DataType>>
struct NthFinderData final
{
    NthFinderData(Container elements, const unsigned int n)
    : elements_{std::move(elements)}
    , n_{n}
    { }

    const Container elements_;
    const unsigned int n_;
};

template <typename DataType, NthElementCompatible Container = std::vector<DataType>>
class NthFinder final : public BaseClass<DataType, Container>
{
public:
    using Iterator = typename Container::iterator;

    NthFinder(NthFinderData<DataType> data)
    : elements_(data.elements_)
    , initialElements_(std::move(data.elements_))
    , n_(data.n_)
    { }

private:
    void resetData() const override
    {
        elements_ = initialElements_;
    }

    Container executeSTL() const override
    {
        Iterator nthIter = elements_.begin();
        std::advance(nthIter, n_);
        
        std::nth_element(elements_.begin(), nthIter, elements_.end());
        return elements_;
    }

    Container executeBoost() const override
    {
        Iterator nthIter = elements_.begin();
        std::advance(nthIter, n_);

        boost::range::nth_element(elements_, nthIter);
        return elements_;
    }

    Container executeSimple() const override
    {
        Iterator nthIter = elements_.begin();
        std::advance(nthIter, n_);

        quickselect(elements_.begin(), elements_.end() - 1, nthIter);

        return elements_;
    }

    Iterator quickselect(Iterator low, Iterator high, const Iterator& nth) const
    {
        while (low < high)
        {
            Iterator pivotIter = partition(low, high);
            if (pivotIter == nth)
                return pivotIter;
            else if (nth < pivotIter)
                high = pivotIter - 1;
            else
                low = pivotIter + 1;
        }
        return low;
    }

    Iterator partition(Iterator low, Iterator high) const
    {
        Iterator mid = low + std::distance(low, high) / 2;
        if (*mid < *low)
            std::iter_swap(low, mid);
        if (*high < *low)
            std::iter_swap(low, high);
        if (*high < *mid)
            std::iter_swap(mid, high);
        
        std::iter_swap(mid, high - 1);
        DataType pivot = *(high - 1);
        Iterator i = low;
        
        for (Iterator j = low; j < high - 1; ++j)
        {
            if (*j < pivot)
            {
                std::iter_swap(i, j);
                ++i;
            }
        }
        
        std::iter_swap(i, high - 1);
        return i;
    }

    mutable Container elements_;
    const Container initialElements_;

public:
    const unsigned int n_;
};

} // namespace src::Algorithms
