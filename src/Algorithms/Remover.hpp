#pragma once

#include "../Concepts/ContainerConcepts.hpp"
#include "Base.hpp"

#include <boost/range/algorithm_ext/erase.hpp> // boost::range::remove_erase_if

using namespace src::Concepts;

namespace src::Algorithms
{

template <typename DataType, typename Container = std::vector<DataType>>
struct RemoverData final
{
    RemoverData(
        const Container elements,
        bool (*const predicate)(const DataType&))
    : elements_{std::move(elements)}
    , predicate_{predicate}
    { }

    const Container elements_;
    bool (*const predicate_)(const DataType&);
};

template <typename DataType, Removable Container = std::vector<DataType>>
class Remover final : public BaseClass<DataType, Container>
{
public:
    Remover(RemoverData<DataType> data)
    : elements_(data.elements_)
    , initialElements_(std::move(data.elements_))
    , predicate_(data.predicate_)
    { }

private:
    void resetData() override
    {
        elements_ = initialElements_;
    }

    Container executeSTL() override
    {
        elements_.erase(
            std::remove_if(elements_.begin(), elements_.end(), predicate_),
            elements_.end());
        return elements_;
    }

    Container executeBoost() override
    {
        boost::range::remove_erase_if(elements_, predicate_);
        return elements_;
    }

    Container executeSimple() override
    {
        auto first = elements_.begin();
        for (auto current = elements_.begin(); current != elements_.end(); ++current)
        {
            if (!predicate_(*current))
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

    Container elements_;
    const Container initialElements_;
    bool (*const predicate_)(const DataType&);
};

} // namespace src::Algorithms
