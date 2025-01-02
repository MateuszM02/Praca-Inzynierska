#pragma once

#include "Base.hpp"
#include <functional>
#include <boost/range/algorithm/generate.hpp> // boost::range::generate

namespace src::Algorithms
{

template <typename GeneratedDataType, typename StateDataType = GeneratedDataType>
class Generator final : public BaseClass<GeneratedDataType, std::vector<GeneratedDataType>>
{
public:
    explicit Generator(const std::size_t n,
        const StateDataType& initialState,
        const std::function<GeneratedDataType(StateDataType&)>& generator)
    : n_{n}
    , initialState_{initialState}
    , currentState_{std::move(initialState)}
    , generator_{std::move(generator)}
    { }

    GeneratedDataType create() const
    {
        return generator_(currentState_);
    }

    std::size_t size() const noexcept { return n_; }

private:
    void resetData() const override
    {
        currentState_ = initialState_;
    }

    std::vector<GeneratedDataType> executeSTL() const override
    {
        std::vector<GeneratedDataType> sequence(n_);
        std::generate(sequence.begin(), sequence.end(), [this]() { return create(); });
        return sequence;
    }

    std::vector<GeneratedDataType> executeBoost() const override
    {
        std::vector<GeneratedDataType> sequence(n_);
        boost::range::generate(sequence, [this]() { return create(); });
        return sequence;
    }

    std::vector<GeneratedDataType> executeSimple() const override
    {
        std::vector<GeneratedDataType> sequence(n_);
        for (GeneratedDataType& element : sequence)
        {
            element = create();
        }
        return sequence;
    }

    std::size_t n_;
    StateDataType initialState_;
    mutable StateDataType currentState_;
    std::function<GeneratedDataType(StateDataType&)> generator_;
};

} // namespace src::Algorithms
