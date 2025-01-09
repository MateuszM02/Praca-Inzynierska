#pragma once

#include "Base.hpp"
#include "../Concepts/ContainerConcepts.hpp"

#include <boost/algorithm/minmax_element.hpp> // boost::minmax_element

using namespace src::Concepts;

namespace src::Algorithms
{

template <Iterable Container>
class MinMaxFinder final : public BaseClass<Container>
{
public:
    using DataType = typename Container::value_type;

    explicit MinMaxFinder(const Container& elements)
    : elements_{std::move(elements)}
    { }

private:
    void resetData() const override { }

    Container executeSTL() const override
    {   
        auto [min, max] = std::minmax_element(elements_.begin(), elements_.end());
        return { *min, *max };
    }

    Container executeBoost() const override
    {
        auto [min, max] = boost::minmax_element(elements_.begin(), elements_.end());
        return { *min, *max };
    }

    Container executeSimple() const override
    {
        auto iter = elements_.begin();
        DataType min = *iter;
        DataType max = *iter;
        ++iter;
        
        while (iter != elements_.end())
        {
            if (*iter < min)
                min = *iter;
            else if (*iter > max)
                max = *iter;
            ++iter;
        }
        return { min, max };
    }

    Container elements_;
};

} // namespace src::Algorithms
