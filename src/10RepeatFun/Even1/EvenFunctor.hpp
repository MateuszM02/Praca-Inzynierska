#pragma once
#include "../Functor.hpp"

// Przyklad 1. Kolejne dodatnie liczby parzyste -------------------------------------------------------------

namespace src::RepeatFun::Even1
{
class EvenFunctor : public Functor<unsigned int>
{
public:
    EvenFunctor();
    unsigned int operator()() override;
private:
    unsigned int x;
};
} // namespace src::RepeatFun::Even1
