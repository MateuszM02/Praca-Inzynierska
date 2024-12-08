#pragma once
#include "../Functor.hpp"

// Przyklad 1. Liczby Fibonacciego --------------------------------------------------------------------------

namespace src::Generate::Fibonacci1
{
template <class Number>
requires std::is_arithmetic_v<Number>
class FibonacciFunctor : public Functor<Number>
{
public:
    FibonacciFunctor(const Number& first, const Number& second);
    Number operator()() override;
    std::shared_ptr<Functor<Number>> clone() const override;
private:
    Number a, b;
};
} // namespace src::Generate::Fibonacci1
