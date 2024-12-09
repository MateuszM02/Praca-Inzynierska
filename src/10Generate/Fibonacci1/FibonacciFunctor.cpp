#include "FibonacciFunctor.hpp"

namespace src::Generate::Fibonacci1
{

template <Addable DataType>
FibonacciFunctor<DataType>::FibonacciFunctor(const DataType& first, const DataType& second) 
: a(first)
, b(second) 
{ }

template <Addable DataType>
DataType FibonacciFunctor<DataType>::operator()()
{
    DataType next = a + b;
    a = b;
    b = next;
    return a;
}

template <Addable DataType>
std::shared_ptr<Functor<DataType>> 
FibonacciFunctor<DataType>::clone() const
{
    return std::make_shared<FibonacciFunctor>(*this);
}

// Jawna instancja klasy zeby dzialaly testy
template class FibonacciFunctor<int>;
template class FibonacciFunctor<double>;

} // namespace src::Generate::Fibonacci1
