#include "MatrixFunctor.hpp"

namespace src::Structures
{
template <class Number>
requires std::is_arithmetic_v<Number>
MatrixFunctor<Number>::MatrixFunctor(const Matrix<Number>& m) 
: originalMatrix(m) 
, currentMatrix(m)
{ }

template <class Number>
requires std::is_arithmetic_v<Number>
Matrix<Number> 
MatrixFunctor<Number>::operator()()
{
    currentMatrix *= originalMatrix;
    return currentMatrix;
}

template <class Number>
requires std::is_arithmetic_v<Number>
std::shared_ptr<Functor<Matrix<Number>>>
MatrixFunctor<Number>::clone() const
{
    return std::make_shared<MatrixFunctor>(*this);
}

// Jawna instancja klasy zeby dzialaly testy
template class MatrixFunctor<int>;
template class MatrixFunctor<double>;

} // namespace src::Structures
