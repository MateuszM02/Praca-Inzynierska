#pragma once

#include "../Base.hpp"
#include "NthFinderHelper.hpp"

#include <boost/range/algorithm/nth_element.hpp> // boost::range::nth_element

namespace src::Algorithms
{

template <typename DataType, NthElementCompatible Container = std::vector<Findable<DataType>>>
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
        elements_ = initialElements_;
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
        auto otherIter = elements_.begin();
        auto nthIter = elements_.begin();
        std::advance(nthIter, n_);

        while (otherIter != nthIter)
        {
            if (*nthIter < *otherIter)
                std::swap(otherIter, nthIter);
            ++otherIter;
        }
        ++otherIter;
        while (otherIter != elements_.end())
        {
            if (*otherIter < *nthIter)
                std::swap(otherIter, nthIter);
            ++otherIter;
        }
        return elements_;
    }

public:
    Container elements_;
    const Container initialElements_;
    const unsigned int n_;
};

} // namespace src::Algorithms
