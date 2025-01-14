#pragma once

#include "Base.hpp"
#include "../Concepts/ContainerConcepts.hpp"
#include "../Structures/CustomPairImpl.hpp"

#include <boost/algorithm/minmax_element.hpp> // boost::minmax_element

using namespace src::Concepts;

namespace src::Algorithms
{

template <Iterable Container>
requires std::is_copy_constructible_v<typename Container::value_type>
class MinMaxFinder final : public BaseClass<CopyablePair<typename Container::value_type>>
{
public:
    using DataType = typename Container::value_type;

    explicit MinMaxFinder(Container&& elements)
    : elements_{std::move(elements)}
    { }

private:
    void resetData() const override { }

    CopyablePair<DataType> executeSTL() const override
    {   
        auto [minIter, maxIter] = std::minmax_element(elements_.begin(), elements_.end());
        return CopyablePair(*minIter, *maxIter);
    }

    CopyablePair<DataType> executeBoost() const override
    {
        auto [minIter, maxIter] = boost::minmax_element(elements_.begin(), elements_.end());
        return CopyablePair(*minIter, *maxIter);
    }

    CopyablePair<DataType> executeSimple() const override
    {
        auto iter = elements_.begin();
        auto minIter = elements_.begin();
        auto maxIter = elements_.begin();
        ++iter;

        while (iter != elements_.end())
        {
            if (*iter < *minIter)
                minIter = iter;
            else if (*iter > *maxIter)
                maxIter = iter;
            ++iter;
        }
        return CopyablePair(*minIter, *maxIter);
    }

    Container elements_;
};

} // namespace src::Algorithms
