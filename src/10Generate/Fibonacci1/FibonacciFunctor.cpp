#include "FibonacciFunctor.hpp"

namespace src::Generate::Fibonacci1
{
template <class Number>
requires std::is_arithmetic_v<Number>
FibonacciFunctor<Number>::FibonacciFunctor(const Number& first, const Number& second) 
: a(first)
, b(second) 
{ }

template <class Number>
requires std::is_arithmetic_v<Number>
Number 
FibonacciFunctor<Number>::operator()()
{
    Number next = a + b;
    a = b;
    b = next;
    return a;
}
} // namespace src::Generate::Fibonacci1