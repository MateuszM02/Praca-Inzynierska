#pragma once

#include <ostream>
#include <vector>

#include "../Concepts/DataTypeConcepts.hpp"
#include "BaseWrapper.hpp"

using namespace src::Concepts;

namespace src::Structures
{

template <Multiplicable DataType> 
using SquareMatrix = std::vector<std::vector<DataType>>;

// klasa trzymajaca 2-wymiarowa, kwadratowa macierz
template <Multiplicable DataType>
class Matrix final : BaseWrapper<DISABLE_MOVE, DISABLE_COPY>
{ 
public:
    // konstruktor domyslny potrzebny do stworzenia wektora elementow
    Matrix()
    : BaseWrapper<DISABLE_MOVE, DISABLE_COPY>({ &n_, &matrix_ })
    , n_(0)
    , matrix_({ { } })
    { }

    Matrix(const SquareMatrix<DataType>& values) 
    : BaseWrapper<DISABLE_MOVE, DISABLE_COPY>({ &n_, &matrix_ })
    , n_(values.size())
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
