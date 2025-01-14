#pragma once

#include "Base.hpp"
#include "../Concepts/DataTypeConcepts.hpp"

#include <ranges> // std::views::transformed
#include <boost/range/adaptor/transformed.hpp> // boost::adaptors::transformed

using namespace src::Concepts;

namespace src::Algorithms
{

template <Transformable InDataType, Transformable ReturnDataType>
class Transformer final : public BaseClass<std::vector<ReturnDataType>>
{
public:
    explicit Transformer(std::vector<InDataType>&& elements,
        ReturnDataType (*const transformer)(const InDataType&))
    : initialElements_{std::move(elements)}
    , transformer_{std::move(transformer)}
    { }

private:
    void resetData() const override { }

    std::vector<ReturnDataType> executeSTL() const override
    {
        auto resultView = initialElements_ | std::views::transform(transformer_);
        std::vector<ReturnDataType> result;
        result.reserve(std::ranges::distance(resultView));
        std::ranges::move(resultView, std::back_inserter(result));
        return result;
    }

    std::vector<ReturnDataType> executeBoost() const override
    {
        auto resultView = initialElements_ | boost::adaptors::transformed(transformer_);
        std::vector<ReturnDataType> result;
        result.reserve(std::ranges::distance(resultView));
        std::ranges::move(resultView, std::back_inserter(result));
        return result;
    }

    std::vector<ReturnDataType> executeSimple() const override
    {
        std::vector<ReturnDataType> result;
        for (const InDataType& element : initialElements_)
        {
            result.emplace_back(transformer_(element));
        }
        return result;
    }

    const std::vector<InDataType> initialElements_;
    ReturnDataType (*const transformer_)(const InDataType&);
};

} // namespace src::Algorithms
