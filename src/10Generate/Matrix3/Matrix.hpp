#pragma once
#include "MatrixConcepts.hpp"

namespace src::Generate::Matrix3
{
// klasa trzymajaca 2-wymiarowa, kwadratowa macierz
template<typename SquareMatrix> 
requires IsSquareMatrix<SquareMatrix> 
class Matrix
{ 
public: 
    Matrix(const SquareMatrix& values) 
    : n(values.size())
    , matrix(values) 
    { } 
    
    size_t size() const { return n; }            
    const auto& at(size_t i, size_t j) const; 

    // Operator mnozenia macierzy 
    Matrix<SquareMatrix> operator*(const Matrix<SquareMatrix>& other) const;

    // operator do wypisywania wartosci macierzy
    template <typename OtherSquareMatrix>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<OtherSquareMatrix>& mat);

private: 
    size_t n; 
    SquareMatrix matrix;
};
} // namespace src::Generate::Matrix3
