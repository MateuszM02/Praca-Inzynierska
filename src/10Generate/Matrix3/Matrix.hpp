#pragma once
#include "MatrixConcepts.hpp"
#define SquareMatrix(T) std::vector<std::vector<T>>

namespace src::Generate::Matrix3
{

// klasa trzymajaca 2-wymiarowa, kwadratowa macierz
template <class Number>
requires std::is_arithmetic_v<Number>
class Matrix
{ 
public: 
    Matrix() : n(0), matrix({ { } }) { }

    Matrix(const SquareMatrix(Number)& values) 
    : n(values.size())
    , matrix(values) 
    { } 
    
    size_t size() const { return n; }            
    const auto& at(size_t i, size_t j) const; 

    // Operator mnozenia macierzy 
    Matrix<Number> operator*=(const Matrix<Number>& other);

    // Operator rownosci elementow macierzy
    bool operator==(const Matrix<Number>& other) const;

    // operator do wypisywania wartosci macierzy
    template <typename OtherNumber>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<OtherNumber>& mat);

private: 
    size_t n; 
    SquareMatrix(Number) matrix;
};
} // namespace src::Generate::Matrix3
