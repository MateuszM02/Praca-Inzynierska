#pragma once

#include "../Concepts/ContainerConcepts.hpp"
#include "Base.hpp"

#include <boost/range/algorithm_ext/erase.hpp> // boost::range::remove_erase_if

using namespace src::Concepts;

namespace src::Algorithms
{

template <typename Container>
struct RemoverData final
{
    using DataType = typename Container::value_type;

    explicit RemoverData(
        const Container& elements,
        bool (*const predicate)(const DataType&)&)
    : elements_{std::move(elements)}
    , predicate_{std::move(predicate)}
    { }

    const Container elements_;
    bool (*const predicate_)(const DataType&);
};

template <Removable Container>
class Remover final : public BaseClass<Container>
{
public:
    using DataType = typename Container::value_type;

    explicit Remover(const RemoverData<Container>& data)
    : elements_{data.elements_}
    , initialElements_{std::move(data.elements_)}
    , predicate_{std::move(data.predicate_)}
    { }

private:
    void resetData() const override
    {
        elements_ = initialElements_;
    }

    Container executeSTL() const override
    {
        elements_.erase(
            std::remove_if(elements_.begin(), elements_.end(), predicate_),
            elements_.end());
        return elements_;
    }

    Container executeBoost() const override
    {
        boost::range::remove_erase_if(elements_, predicate_);
        return elements_;
    }

    Container executeSimple() const override
    {
        auto first = elements_.begin();
        for (auto current = elements_.begin(); current != elements_.end(); ++current)
        {
            if (not predicate_(*current))
            {
                if (first != current)
                {
                    *first = std::move(*current);
                }
                ++first;
            }
        }
        elements_.erase(first, elements_.end());
        return elements_;
    }

    mutable Container elements_;
    const Container initialElements_;
    bool (*const predicate_)(const DataType&);
};

} // namespace src::Algorithms
