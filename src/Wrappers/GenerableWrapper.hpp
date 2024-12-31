
#pragma once

#include "BaseWrapper.hpp"

namespace src::Wrappers
{

// klasa przechowujaca stan obiektu modyfikowany operatorem()
// podczas wywolywania std::generate/boost::range::generate
template <typename GeneratedDataType, typename StateDataType = GeneratedDataType>
class GenerableWrapper final : public BaseWrapper<StateDataType, ENABLE_MOVE, ENABLE_COPY>
{
public:
    GenerableWrapper(const unsigned int n,
            const StateDataType& initialState,
            std::function<GeneratedDataType(const StateDataType&, StateDataType&)> generator)
    : BaseWrapper<StateDataType, ENABLE_MOVE, ENABLE_COPY>(initialState)
    , n_{n}
    , currentState_{std::move(initialState)}
    , generator_{std::move(generator)}
    { }

    GeneratedDataType operator()()
    {
        return generator_(this->getValue(), currentState_);
    }

    void reset() const
    {
        currentState_ = this->getValue();
    }

    unsigned int N() const { return n_; }

private:
    unsigned int n_;
    mutable StateDataType currentState_;
    std::function<GeneratedDataType(const StateDataType&, StateDataType&)> generator_;

protected:
    std::vector<void*> getClassFields() override
    {
        return { &n_, &currentState_, &generator_ };
    }
};

} // namespace src::Wrappers
