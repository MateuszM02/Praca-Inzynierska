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

template <class Number>
requires std::is_arithmetic_v<Number>
std::shared_ptr<Functor<Number>> 
FibonacciFunctor<Number>::clone() const
{
    return std::make_shared<FibonacciFunctor>(*this);
}

// Jawna instancja klasy zeby dzialaly testy
template class FibonacciFunctor<int>;
template class FibonacciFunctor<double>;

} // namespace src::Generate::Fibonacci1
