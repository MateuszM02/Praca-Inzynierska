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
            newMatrix.set(row, col, m1.get(row, col) + m2.get(row, col));
        }
    }
    return newMatrix;
}

// TODO: zmienic na koncept DivisibleByConst, ktory na razie nie dziala
template <typename DataType>
Matrix<DataType> operator/(const Matrix<DataType>& m, const unsigned int div)
{
    Matrix<DataType> newMatrix(m);
    for (size_t row = 0; row < m.size(); ++row)
    {
        for (size_t col = 0; col < m.size(); ++col)
        {
            newMatrix.set(row, col, m.get(row, col) / div);
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
            m1.set(row, col, m1.get(row, col) + m2.get(row, col));
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
            m1.set(row, col, value);
        }
    }

    return m1;
}

template <Comparable DataType>
requires SameShape<Matrix<DataType>>
bool operator==(const Matrix<DataType>& m1, const Matrix<DataType>& m2)
{
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

// TODO: stworzyc koncept Printable?
template <typename OtherDataType>
std::ostream& operator<<(std::ostream& os, const Matrix<OtherDataType>& m) 
{
    for (size_t row = 0; row < m.size(); ++row)
    {
        for (size_t col = 0; col < m.size(); ++col)
        {
            os << m.get(row, col) << " ";
        }
    }
    return os;
}

class MatrixImpl final
{
public:
    MatrixImpl() = delete;

    template <Multiplicable Number>
    static Matrix<Number> creator(const Matrix<Number>& initialState, Matrix<Number>& currentState)
    {
        currentState *= initialState;
        return currentState;
    }

    template <Multiplicable Number>
    static std::shared_ptr<Generator<Matrix<Number>>>
    createGenerator(const unsigned int n, const Matrix<Number>& initialMatrix) 
    {
        const Generator<Matrix<Number>> generator(n, initialMatrix, creator);
        return std::make_shared<Generator<Matrix<Number>>>(std::move(generator));
    }
};

} // namespace src::Structures

namespace std
{

template <HasNumericLimits DataType>
class numeric_limits<src::Structures::Matrix<DataType>>
{
public:
    static const bool is_specialized = true;
    
    static src::Structures::Matrix<DataType> min()
    {
        return src::Structures::Matrix<DataType>(
            std::numeric_limits<std::vector<std::vector<DataType>>>::min());
    }
    
    static src::Structures::Matrix<DataType> max()
    {
        return src::Structures::Matrix<DataType>(
            std::numeric_limits<std::vector<std::vector<DataType>>>::max());
    }
    
    static src::Structures::Matrix<DataType> lowest()
    {
        return src::Structures::Matrix<DataType>(
            std::numeric_limits<std::vector<std::vector<DataType>>>::lowest());
    }
    
    static src::Structures::Matrix<DataType> epsilon()
    {
        return src::Structures::Matrix<DataType>(
            std::numeric_limits<std::vector<std::vector<DataType>>>::epsilon());
    }
};

} // namespace std
