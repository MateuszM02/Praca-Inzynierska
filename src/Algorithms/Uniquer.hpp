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
        auto removedRange = std::ranges::unique(filteredElements_);
        filteredElements_.erase(removedRange.begin(), removedRange.end());
        return filteredElements_;
    }

    std::vector<DataType> executeBoost() const override
    {
        auto resultView = filteredElements_ | boost::adaptors::uniqued;
        return std::vector<DataType>(resultView.begin(), resultView.end());
    }

    std::vector<DataType> executeSimple() const override
    {
        if (filteredElements_.empty()) return filteredElements_;

        std::size_t removedElements = 0;
        std::size_t begin = 0;

        while (begin < filteredElements_.size() - removedElements)
        {
            std::size_t end = begin + 1;
            while (end < filteredElements_.size() - removedElements &&
                filteredElements_[begin] == filteredElements_[end])
            {
                end++;
            }

            std::size_t moveDiff = end - begin - 1;
            begin++;
            if (moveDiff < 1)   continue;

            for (std::size_t k = begin; k < filteredElements_.size() - removedElements - moveDiff; k++)
            {
                filteredElements_[k] = std::move(filteredElements_[k + moveDiff]);
            }
            removedElements += moveDiff;
        }

        filteredElements_.erase(filteredElements_.end() - removedElements, filteredElements_.end());
        return filteredElements_;
    }

    const std::vector<DataType> initialElements_;
    mutable std::vector<DataType> filteredElements_;
};

} // namespace src::Algorithms
