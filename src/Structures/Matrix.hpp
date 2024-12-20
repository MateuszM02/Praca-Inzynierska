#pragma once

#include "../Algorithms/10Generate/Generator.hpp"

using namespace src::Algorithms;

namespace src::Structures
{

template <Multiplicable DataType> 
using SquareMatrix = std::vector<std::vector<DataType>>;

// klasa trzymajaca 2-wymiarowa, kwadratowa macierz
template <Multiplicable DataType>
class Matrix final
{ 
public: 
    Matrix() : n_(0), matrix_({ { } }) { }

    Matrix(const SquareMatrix<DataType>& values) 
    : n_(values.size())
    , matrix_(values) 
    { } 
    
    size_t size() const { return n_; }            
    const DataType& at(size_t i, size_t j) const; 

    // Operator mnozenia macierzy 
    Matrix<DataType> operator*=(const Matrix<DataType>& other);

    // Operator rownosci elementow macierzy
    bool operator==(const Matrix<DataType>& other) const;

    // operator do wypisywania wartosci macierzy
    template <Multiplicable OtherDataType>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<OtherDataType>& mat);

private: 
    size_t n_; 
    SquareMatrix<DataType> matrix_;
};
} // namespace src::Structures
