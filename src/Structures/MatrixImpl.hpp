#pragma once

#include "../Algorithms/Generator.hpp"
#include "Matrix.hpp"

using namespace src::Algorithms;
using namespace src::Concepts;

namespace src::Structures
{

template <typename MatrixType>
concept SameShape = requires(const MatrixType& m1, const MatrixType& m2)
{
    { m1.size() } -> std::convertible_to<std::size_t>;
    { m2.size() } -> std::convertible_to<std::size_t>;
    { m1.size() == m2.size() } -> std::convertible_to<bool>;
};

// implementacja operatorow potrzebnych do testow na klasie Matrix
template <Addable DataType>
requires SameShape<Matrix<DataType>>
Matrix<DataType> operator+(const Matrix<DataType>& m1, const Matrix<DataType>& m2)
{
    Matrix<DataType> newMatrix(m1);
    for (size_t row = 0; row < m1.size(); ++row)
    {
        for (size_t col = 0; col < m1.size(); ++col)
        {
            newMatrix.update(row, col, m1.get(row, col) + m2.get(row, col));
        }
    }
    return newMatrix;
}

template <DivisibleByConst DataType>
Matrix<DataType> operator/(const Matrix<DataType>& m, const unsigned int div)
{
    Matrix<DataType> newMatrix(m);
    for (size_t row = 0; row < m.size(); ++row)
    {
        for (size_t col = 0; col < m.size(); ++col)
        {
            newMatrix.update(row, col, m.get(row, col) / div);
        }
    }
    return newMatrix;
}

template <Multiplicable DataType>
requires SameShape<Matrix<DataType>>
Matrix<DataType>& operator+=(Matrix<DataType>& m1, const Matrix<DataType>& m2)
{
    for (size_t row = 0; row < m1.size(); ++row)
    {
        for (size_t col = 0; col < m1.size(); ++col)
        {
            m1.update(row, col, m1.get(row, col) + m2.get(row, col));
        }
    }
    return m1;
}

template <Multiplicable DataType>
requires SameShape<Matrix<DataType>>
Matrix<DataType>& operator*=(Matrix<DataType>& m1, const Matrix<DataType>& m2)
{
    for (size_t row = 0; row < m1.size(); ++row)
    {
        for (size_t col = 0; col < m1.size(); ++col)
        {
            DataType value(0);
            for (size_t k = 0; k < m1.size(); ++k)
            {
                value += m1.get(row, k) * m2.get(k, col);
            }
            m1.update(row, col, value);
        }
    }

    return m1;
}

template <Comparable DataType>
requires SameShape<Matrix<DataType>>
bool operator==(const Matrix<DataType>& m1, const Matrix<DataType>& m2)
{
    if (m1.size() != m2.size())
        return false;

    for (size_t row = 0; row < m1.size(); ++row)
    {
        for (size_t col = 0; col < m1.size(); ++col)
        {
            if (m1.get(row, col) != m2.get(row, col))
                return false;
        }
    }

    return true;
}

template <typename DataType>
bool operator!=(const Matrix<DataType>& m1, const Matrix<DataType>& m2)
{
    return !(m1 == m2);
}

template <Comparable DataType>
requires SameShape<Matrix<DataType>>
bool operator<(const Matrix<DataType>& m1, const Matrix<DataType>& m2)
{
    for (size_t row = 0; row < m1.size(); ++row)
    {
        for (size_t col = 0; col < m1.size(); ++col)
        {
            if (m1.get(row, col) < m2.get(row, col))
                return true;
            else if (m1.get(row, col) > m2.get(row, col))
                return false;
        }
    }

    return false;
}

template <typename DataType>
bool operator>(const Matrix<DataType>& m1, const Matrix<DataType>& m2)
{
    return m2 < m1;
}

template <Printable DataType>
std::ostream& operator<<(std::ostream& os, const Matrix<DataType>& m) 
{
    for (size_t row = 0; row < m.size(); ++row)
    {
        os << "\n[";
        for (size_t col = 0; col < m.size(); ++col)
        {
            os << m.get(row, col) << ", ";
        }
        os << "]";
    }
    return os;
}

} // namespace src::Structures

namespace std
{

template <HasNumericLimits DataType>
class numeric_limits<src::Structures::Matrix<DataType>>
{
public:
    static constexpr bool is_specialized = true;
    
    static src::Structures::Matrix<DataType> min() noexcept
    {
        static vector<vector<DataType>> v = { { numeric_limits<DataType>::min() } };
        static src::Structures::Matrix<DataType> m(v);
        return m;
    } 
    
    static src::Structures::Matrix<DataType> max() noexcept
    {
        static vector<vector<DataType>> v = { { numeric_limits<DataType>::max() } };
        static src::Structures::Matrix<DataType> m(v);
        return m;
    }
    
    static src::Structures::Matrix<DataType> lowest() noexcept
    {
        static vector<vector<DataType>> v = { { numeric_limits<DataType>::lowest() } };
        static src::Structures::Matrix<DataType> m(v);
        return m;
    }
    
    static src::Structures::Matrix<DataType> epsilon() noexcept
    {
        static vector<vector<DataType>> v = { { numeric_limits<DataType>::epsilon() } };
        static src::Structures::Matrix<DataType> m(v);
        return m;
    }
};

} // namespace std
