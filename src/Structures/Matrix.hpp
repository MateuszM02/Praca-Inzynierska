#pragma once

#include <ostream>
#include <vector>

#include "../Concepts/DataTypeConcepts.hpp"
#include "BaseWrapper.hpp"

using namespace src::Concepts;

namespace src::Structures
{

template <typename DataType>
concept SquareMatrix = requires(DataType matrix)
{
    { matrix.size() } -> std::convertible_to<std::size_t>;
    { matrix[0].size() } -> std::convertible_to<std::size_t>;
    { matrix.size() == matrix[0].size() } -> std::convertible_to<bool>;
    requires std::is_same_v<
        typename DataType::value_type,
        std::vector<typename DataType::value_type::value_type>>;
};

// klasa trzymajaca 2-wymiarowa, kwadratowa macierz
template <typename DataType>
class Matrix final : BaseWrapper<DISABLE_MOVE, ENABLE_COPY>
{
public:
    // konstruktor domyslny potrzebny do stworzenia wektora elementow
    Matrix()
    : BaseWrapper<DISABLE_MOVE, ENABLE_COPY>({ &n_, &matrix_ })
    , n_(0)
    , matrix_({ { } })
    { }

    template <SquareMatrix MatrixVector> 
    Matrix(const MatrixVector& values)
    : BaseWrapper<DISABLE_MOVE, ENABLE_COPY>({ &n_, &matrix_ })
    , n_(values.size())
    , matrix_(values)
    { }
    
    std::size_t size() const noexcept { return n_; }

    const DataType& get(const size_t row, const size_t col) const
    {
        if (row >= n_ || col >= n_)
        {
            throw std::out_of_range("Index out of range.");
        }
        return matrix_[row][col];
    }

    void set(const size_t row, const size_t col, const DataType& newValue) const
    {
        if (row >= n_ || col >= n_)
        {
            throw std::out_of_range("Index out of range.");
        }
        matrix_[row][col] = std::move(newValue);
    }

private:
    std::size_t n_;
    mutable std::vector<std::vector<DataType>> matrix_;
};

} // namespace src::Structures
