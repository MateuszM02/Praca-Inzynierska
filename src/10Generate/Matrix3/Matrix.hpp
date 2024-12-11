#pragma once
#include "../Functor.hpp"
#include "../../Concepts.hpp"

namespace src::Generate::Matrix3
{

template <Multiplicable DataType> 
using SquareMatrix = std::vector<std::vector<DataType>>;

// klasa trzymajaca 2-wymiarowa, kwadratowa macierz
template <Multiplicable DataType>
class Matrix
{ 
public: 
    Matrix() : n(0), matrix({ { } }) { }

    Matrix(const SquareMatrix<DataType>& values) 
    : n(values.size())
    , matrix(values) 
    { } 
    
    size_t size() const { return n; }            
    const DataType& at(size_t i, size_t j) const; 

    // Operator mnozenia macierzy 
    Matrix<DataType> operator*=(const Matrix<DataType>& other);

    // Operator rownosci elementow macierzy
    bool operator==(const Matrix<DataType>& other) const;

    // operator do wypisywania wartosci macierzy
    template <Multiplicable OtherDataType>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<OtherDataType>& mat);

private: 
    size_t n; 
    SquareMatrix<DataType> matrix;
};
} // namespace src::Generate::Matrix3
