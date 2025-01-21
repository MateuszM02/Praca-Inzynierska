#pragma once

#include "Base.hpp"
#include "../Concepts/DataTypeConcepts.hpp"

#include <boost/range/adaptor/uniqued.hpp> // boost::adaptors::uniqued

using namespace src::Concepts;

namespace src::Algorithms
{

template <EqualityComparable DataType>
requires std::is_copy_constructible_v<DataType>
class Uniquer final : public BaseClass<std::vector<DataType>>
{
public:
    explicit Uniquer(std::vector<DataType>&& elements)
    : initialElements_{elements}
    , filteredElements_{std::move(elements)}
    { }

private:
    void resetData() const override
    {
        filteredElements_ = initialElements_;
    }

    std::vector<DataType> executeSTL() const override
    {
        std::vector<DataType> result;
        auto resultView = std::ranges::unique(filteredElements_);
        result.reserve(initialElements_.size() - resultView.size());
        std::ranges::move(filteredElements_.begin(), resultView.begin(), std::back_inserter(result));
        return result;
    }

    std::vector<DataType> executeBoost() const override
    {
        auto resultView = filteredElements_ | boost::adaptors::uniqued;
        std::vector<DataType> result;
        result.reserve(std::distance(resultView.begin(), resultView.end()));
        std::ranges::move(resultView, std::back_inserter(result));
        return result;
    }

    std::vector<DataType> executeSimple() const override
    {
        if (filteredElements_.empty()) return filteredElements_;

        auto writeIter = filteredElements_.begin();
        for (auto readIter = std::next(filteredElements_.begin());
            readIter != filteredElements_.end(); ++readIter)
        {
            if (*readIter != *writeIter)
            {
                ++writeIter;
                *writeIter = std::move(*readIter);
            }
        }

        auto newSize = std::distance(filteredElements_.begin(), std::next(writeIter));
        filteredElements_.resize(newSize);
        return filteredElements_;
    }

    const std::vector<DataType> initialElements_;
    mutable std::vector<DataType> filteredElements_;
};

} // namespace src::Algorithms
