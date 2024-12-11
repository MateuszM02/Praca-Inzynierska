#pragma once
#include "../Functor.hpp"
#include "../../Concepts.hpp"

// Przyklad 1. Liczby Fibonacciego --------------------------------------------------------------------------

namespace src::Generate::Fibonacci1
{

template <Addable DataType>
class FibonacciFunctor : public Functor<DataType>
{
public:
    FibonacciFunctor(const DataType& first, const DataType& second);
    DataType operator()() override;
    std::shared_ptr<Functor<DataType>> clone() const override;
private:
    DataType a, b;
};

} // namespace src::Generate::Fibonacci1
