#pragma once

#include "Base.hpp"
#include "../Wrappers/GenerableWrapper.hpp"

#include <boost/range/algorithm/generate.hpp> // boost::range::generate

using namespace src::Wrappers;

namespace src::Algorithms
{

template <typename GeneratedDataType, typename StateDataType = GeneratedDataType>
class Generator final : public BaseClass<GeneratedDataType, std::vector<GeneratedDataType>>
{
public:
    Generator(GenerableWrapper<GeneratedDataType, StateDataType> data)
    : state_{std::move(data)}
    { }

    unsigned int size() const { return state_.N(); }

private:
    void resetData() override
    {
        state_.reset();
    }

    std::vector<GeneratedDataType> executeSTL() override
    {
        std::vector<GeneratedDataType> sequence(state_.N());
        std::generate(sequence.begin(), sequence.end(), [this]() { return state_(); });
        return sequence;
    }

    std::vector<GeneratedDataType> executeBoost() override
    {
        std::vector<GeneratedDataType> sequence(state_.N());
        boost::range::generate(sequence, [this]() { return state_(); });
        return sequence;
    }

    std::vector<GeneratedDataType> executeSimple() override
    {
        std::vector<GeneratedDataType> sequence(state_.N());
        for (GeneratedDataType& element : sequence)
        {
            element = state_();
        }
        return sequence;
    }

    GenerableWrapper<GeneratedDataType, StateDataType> state_;
};

} // namespace src::Algorithms
