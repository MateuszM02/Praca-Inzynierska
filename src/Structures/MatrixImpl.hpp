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
    { m1.size() == m2.size() } -> std::same_as<bool>;
};

template <DivisibleByConst DataType, bool MoveEnabled, bool CopyEnabled>
Matrix<DataType, MoveEnabled, CopyEnabled> operator/(
    const Matrix<DataType, MoveEnabled, CopyEnabled>& m,
    const unsigned int div)
{
    Matrix<DataType, MoveEnabled, CopyEnabled> newMatrix(m);
    for (size_t row = 0; row < m.size(); ++row)
    {
        for (size_t col = 0; col < m.size(); ++col)
        {
            newMatrix.update(row, col, m.get(row, col) / div);
        }
    }
    return newMatrix;
}

template <Multiplicable DataType, bool MoveEnabled, bool CopyEnabled>
requires SameShape<Matrix<DataType, MoveEnabled, CopyEnabled>>
Matrix<DataType, MoveEnabled, CopyEnabled>& operator+=(
    Matrix<DataType, MoveEnabled, CopyEnabled>& m1,
    const Matrix<DataType, MoveEnabled, CopyEnabled>& m2)
{
    // potrzebne do 2Accumulate, bo domyslny konstruktor ktorego uzywa tworzy pusta macierz
    if (m1.size() == 0)
    {
        m1 = m2;
        return m1;
    }

    for (size_t row = 0; row < m1.size(); ++row)
    {
        for (size_t col = 0; col < m1.size(); ++col)
        {
            m1.update(row, col, m1.get(row, col) + m2.get(row, col));
        }
    }
    return m1;
}

template <Multiplicable DataType, bool MoveEnabled, bool CopyEnabled>
requires SameShape<Matrix<DataType, MoveEnabled, CopyEnabled>>
Matrix<DataType, MoveEnabled, CopyEnabled>& operator*=(
    Matrix<DataType, MoveEnabled, CopyEnabled>& m1,
    const Matrix<DataType, MoveEnabled, CopyEnabled>& m2)
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

template <Comparable DataType, bool MoveEnabled, bool CopyEnabled>
requires SameShape<Matrix<DataType, MoveEnabled, CopyEnabled>>
bool operator==(
    const Matrix<DataType, MoveEnabled, CopyEnabled>& m1,
    const Matrix<DataType, MoveEnabled, CopyEnabled>& m2)
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

template <typename DataType, bool MoveEnabled, bool CopyEnabled>
bool operator!=(
    const Matrix<DataType, MoveEnabled, CopyEnabled>& m1,
    const Matrix<DataType, MoveEnabled, CopyEnabled>& m2)
{
    return !(m1 == m2);
}

template <Comparable DataType, bool MoveEnabled, bool CopyEnabled>
requires SameShape<Matrix<DataType, MoveEnabled, CopyEnabled>>
bool operator<(
    const Matrix<DataType, MoveEnabled, CopyEnabled>& m1,
    const Matrix<DataType, MoveEnabled, CopyEnabled>& m2)
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

template <typename DataType, bool MoveEnabled, bool CopyEnabled>
bool operator>(
    const Matrix<DataType, MoveEnabled, CopyEnabled>& m1,
    const Matrix<DataType, MoveEnabled, CopyEnabled>& m2)
{
    return m2 < m1;
}

template <Printable DataType, bool MoveEnabled, bool CopyEnabled>
std::ostream& operator<<(std::ostream& os,
    const Matrix<DataType, MoveEnabled, CopyEnabled>& m)
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

template <HasNumericLimits DataType, bool MoveEnabled, bool CopyEnabled>
class numeric_limits<src::Structures::Matrix<DataType, MoveEnabled, CopyEnabled>>
{
public:
    static constexpr bool is_specialized = true;

    static src::Structures::Matrix<DataType, MoveEnabled, CopyEnabled> min() noexcept
    {
        std::vector<std::vector<DataType>> vec =
            { { std::numeric_limits<DataType>::min() } };
        return src::Structures::Matrix<DataType, MoveEnabled, CopyEnabled>(std::move(vec));
    }

    static src::Structures::Matrix<DataType, MoveEnabled, CopyEnabled> max() noexcept
    {
        std::vector<std::vector<DataType>> vec =
            { { std::numeric_limits<DataType>::max() } };
        return src::Structures::Matrix<DataType, MoveEnabled, CopyEnabled>(std::move(vec));
    }

    static src::Structures::Matrix<DataType, MoveEnabled, CopyEnabled> lowest() noexcept
    {
        std::vector<std::vector<DataType>> vec =
            { { std::numeric_limits<DataType>::lowest() } };
        return src::Structures::Matrix<DataType, MoveEnabled, CopyEnabled>(std::move(vec));
    }

    static src::Structures::Matrix<DataType, MoveEnabled, CopyEnabled> epsilon() noexcept
    {
        std::vector<std::vector<DataType>> vec =
            { { std::numeric_limits<DataType>::epsilon() } };
        return src::Structures::Matrix<DataType, MoveEnabled, CopyEnabled>(std::move(vec));
    }
};

} // namespace std
