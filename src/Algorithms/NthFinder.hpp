#pragma once

#include "Base.hpp"
#include "DataWrapper.hpp"
#include "../Concepts/ContainerConcepts.hpp"

#include <boost/range/algorithm/nth_element.hpp> // boost::range::nth_element

using namespace src::Concepts;

namespace src::Algorithms
{

template <typename DataType, NthElementCompatible Container = std::vector<DataWrapper<DataType>>>
struct NthFinderData final
{
    NthFinderData(Container elements, const unsigned int n)
    : elements_{std::move(elements)}
    , n_{n}
    { }

    const Container elements_;
    const unsigned int n_;
};

template <typename DataType, NthElementCompatible Container = std::vector<DataWrapper<DataType>>>
class NthFinder final : public BaseClass<DataType, Container>
{
public:
    NthFinder(NthFinderData<DataType> data)
    : elements_(data.elements_)
    , initialElements_(std::move(data.elements_))
    , n_(data.n_)
    { }

private:
    void resetData() override
    {
        auto elementIter = elements_.begin();
        auto initialElementIter = initialElements_.begin();

        while (elementIter != elements_.end())
        {
            *elementIter = *initialElementIter;
            ++elementIter;
            ++initialElementIter;
        }
    }

    Container executeSTL() override
    {
        auto nthIter = elements_.begin();
        std::advance(nthIter, n_);
        
        std::nth_element(elements_.begin(), nthIter, elements_.end());
        return elements_;
    }

    Container executeBoost() override
    {
        auto nthIter = elements_.begin();
        std::advance(nthIter, n_);

        boost::range::nth_element(elements_, nthIter);
        return elements_;
    }

    Container executeSimple() override
    {
        auto nthIter = elements_.begin();
        std::advance(nthIter, n_);

        quickselect(elements_.begin(), elements_.end() - 1, nthIter);

        return elements_;
    }

    template<typename Iter>
    Iter partition(Iter low, Iter high)
    {
        DataWrapper<DataType> pivot = *high;
        Iter i = low;

        for (Iter j = low; j < high; ++j)
        {
            if (*j < pivot)
            {
                std::iter_swap(i, j);
                ++i;
            }
        }
        std::iter_swap(i, high);
        return i;
    }

    template<typename Iter>
    Iter quickselect(Iter low, Iter high, Iter nth)
    {
        if (low == high)    return low;

        Iter pivotIter = partition(low, high);

        if (pivotIter == nth)
            return pivotIter;
        else if (nth < pivotIter)
            return quickselect(low, pivotIter - 1, nth);
        else
            return quickselect(pivotIter + 1, high, nth);
    }

    Container elements_;
    const Container initialElements_;

public:
    const unsigned int n_;
};

} // namespace src::Algorithms
