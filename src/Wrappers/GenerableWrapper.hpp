
#pragma once

#include "BaseWrapper.hpp"

#include <functional>

namespace src::Wrappers
{

// klasa przechowujaca stan obiektu modyfikowany operatorem()
// podczas wywolywania std::generate/boost::range::generate
template <typename GeneratedDataType, typename StateDataType = GeneratedDataType>
requires std::is_copy_assignable_v<GeneratedDataType> &&
         std::is_copy_assignable_v<StateDataType>
class GenerableWrapper : virtual public BaseWrapper<StateDataType>
{
public:
    GenerableWrapper(const unsigned int n,
            const StateDataType& initialState,
            std::function<GeneratedDataType(const StateDataType&, StateDataType&)> generator)
    : BaseWrapper<StateDataType>(initialState)
    , n_{n}
    , currentState_{std::move(initialState)}
    , generator_{std::move(generator)}
    { }

    GeneratedDataType operator()()
    {
        return generator_(this->getValue(), currentState_);
    }

    void reset()
    {
        currentState_ = this->getValue();
    }

    unsigned int N() const { return n_; }

private:
    const unsigned int n_;
    StateDataType currentState_;
    std::function<GeneratedDataType(const StateDataType&, StateDataType&)> generator_;
};

} // namespace src::Wrappers
