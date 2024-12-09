#pragma once
#include "../Functor.hpp"

// Przyklad 1. Liczby Fibonacciego --------------------------------------------------------------------------

namespace src::Generate::Fibonacci1
{

template <typename DataType>
concept Addable = requires(DataType a, DataType b)
{
    { a + b } -> std::convertible_to<DataType>;
};

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
