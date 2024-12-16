#pragma once

#include "Base.hpp"
#include "GeneratorHelper.hpp"

#include <boost/range/algorithm/generate.hpp> // boost::range::generate

namespace src::Algorithms
{

template <typename GeneratedDataType, typename StateDataType = GeneratedDataType>
class Generator final : public BaseClass<GeneratedDataType, std::vector<GeneratedDataType>>
{
public:
    Generator(GeneratorData<GeneratedDataType, StateDataType> data)
    : BaseClass<GeneratedDataType, std::vector<GeneratedDataType>>(std::move(data.expectedResult_))
    , state_{std::move(data)}
    { }

    unsigned int size() const { return this->state_.n_; }

private:
    void resetData() override
    {
        state_.reset();
    }

    std::vector<GeneratedDataType> executeSTL() override
    {
        std::vector<GeneratedDataType> sequence(this->state_.n_);
        std::generate(sequence.begin(), sequence.end(), [this]() { return this->state_(); });
        return sequence;
    }

    std::vector<GeneratedDataType> executeBoost() override
    {
        std::vector<GeneratedDataType> sequence(this->state_.n_);
        boost::range::generate(sequence, [this]() { return this->state_(); });
        return sequence;
    }

    std::vector<GeneratedDataType> executeSimple() override
    {
        std::vector<GeneratedDataType> sequence(this->state_.n_);
        for (GeneratedDataType& element : sequence)
        {
            element = this->state_();
        }
        return sequence;
    }

    GeneratorData<GeneratedDataType, StateDataType> state_;
};

} // namespace src::Algorithms
