#pragma once
#include "../Functor.hpp"

namespace src::Generate::Matrix3
{

template <class Number> 
using SquareMatrix = std::vector<std::vector<Number>>;

// klasa trzymajaca 2-wymiarowa, kwadratowa macierz
template <class Number>
requires std::is_arithmetic_v<Number>
class Matrix
{ 
public: 
    Matrix() : n(0), matrix({ { } }) { }

    Matrix(const SquareMatrix<Number>& values) 
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
    SquareMatrix<Number> matrix;
};
} // namespace src::Generate::Matrix3
