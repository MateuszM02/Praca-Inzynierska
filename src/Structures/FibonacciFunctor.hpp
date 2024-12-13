#pragma once
#include "../Algorithms/Functor.hpp"

using namespace src::Algorithms;

namespace src::Structures
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

} // namespace src::Structures
