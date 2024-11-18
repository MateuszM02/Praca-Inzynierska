#pragma once
#include "../Functor.hpp"

// Przyklad 2. Liczby Fibonacciego --------------------------------------------------------------------------

namespace src::RepeatFun::Fibonacci2
{
template <class Number>
requires std::is_arithmetic_v<Number>
class FibonacciFunctor : public Functor<Number>
{
public:
    FibonacciFunctor(const Number& first, const Number& second);
    Number operator()() override;
private:
    Number a, b;
};
} // namespace src::RepeatFun::Fibonacci2
