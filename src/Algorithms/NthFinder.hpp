#pragma once

#include "Base.hpp"
#include "../Concepts/ContainerConcepts.hpp"

#include <boost/range/algorithm/nth_element.hpp> // boost::range::nth_element

using namespace src::Concepts;

namespace src::Algorithms
{

template <typename Container>
struct NthFinderData final
{
    explicit NthFinderData(Container&& elements, const std::size_t n)
    : elements_{std::move(elements)}
    , n_{n}
    { }

    Container elements_;
    const std::size_t n_;
};

template <NthElementCompatible Container>
requires std::is_copy_constructible_v<typename Container::value_type>
class NthFinder final : public BaseClass<Container>
{
public:
    using DataType = typename Container::value_type;
    using Iterator = typename Container::iterator;

    explicit NthFinder(NthFinderData<Container>&& data)
    : elements_{data.elements_}
    , initialElements_{std::move(data.elements_)}
    , n_{data.n_}
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

    Iterator quickselect(Iterator low, Iterator high, const Iterator& nthIter) const
    {
        while (low < high)
        {
            Iterator pivotIter = partition(low, high);
            if (pivotIter == nthIter)
                return pivotIter;
            else if (nthIter < pivotIter)
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
        Iterator i = low;

        for (Iterator j = low; j < high - 1; ++j)
        {
            if (*j < *(high - 1)) // j < pivot
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
    const std::size_t n_;
};

} // namespace src::Algorithms
