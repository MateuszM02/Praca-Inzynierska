
#pragma once

#include <functional>

namespace src::Algorithms
{

// klasa przechowujaca stan obiektu modyfikowany operatorem()
// podczas wywolywania std::generate/boost::range::generate
template <typename GeneratedDataType, typename StateDataType = GeneratedDataType>
requires std::is_copy_assignable_v<GeneratedDataType> &&
         std::is_copy_assignable_v<StateDataType>
struct GeneratorData final
{
    GeneratorData(const unsigned int n,
            const StateDataType& initialState,
            std::function<GeneratedDataType(const StateDataType&, StateDataType&)> g)
    : n_{n}
    , initialState_{initialState}
    , currentState_{initialState}
    , generator_{std::move(g)}
    { }

    GeneratedDataType operator()()
    {
        return generator_(initialState_, currentState_);
    }

    void reset()
    {
        currentState_ = initialState_;
    }

    const unsigned int n_;
    const StateDataType initialState_;
    StateDataType currentState_;

private:
    std::function<GeneratedDataType(const StateDataType&, StateDataType&)> generator_;
};

} // namespace src::Algorithms
