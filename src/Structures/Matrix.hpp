#pragma once

#include <iostream>
#include <vector>

#include <assert.h>

#include "../Concepts/DataTypeConcepts.hpp"
#include "BaseWrapper.hpp"

#define ASSERT_INDEX(indexName) \
    if ((indexName) >= matrix_.size()) \
    { \
        std::cerr << #indexName << " index out of range, given: " \
            << (indexName) << ", size: " << matrix_.size() << "\n"; \
        assert((indexName) < matrix_.size()); \
    }

using namespace src::Concepts;

namespace src::Structures
{

template <typename MatrixVector>
concept SquareMatrix = requires(const MatrixVector& matrix)
{
    { matrix.size() } -> std::convertible_to<std::size_t>;
    { matrix[0].size() } -> std::convertible_to<std::size_t>;
    { matrix.size() == matrix[0].size() } -> std::convertible_to<bool>;
    requires std::is_same_v<
        typename MatrixVector::value_type,
        std::vector<typename MatrixVector::value_type::value_type>>;
};

// klasa trzymajaca 2-wymiarowa, kwadratowa macierz
template <typename DataType, bool MoveEnabled, bool CopyEnabled>
class Matrix final : BaseWrapper<MoveEnabled, CopyEnabled>
{
public:
    // potrzebne do 2Accumulate
    explicit Matrix()
    : BaseWrapper<MoveEnabled, CopyEnabled>({ &matrix_ })
    , matrix_{}
    { }

    template <SquareMatrix MatrixVector>
    explicit Matrix(MatrixVector&& values)
    : BaseWrapper<MoveEnabled, CopyEnabled>({ &matrix_ })
    , matrix_{std::move(values)}
    { }

    std::size_t size() const { return matrix_.size(); }

    DataType get(const size_t row, const size_t col) const
    {
        ASSERT_INDEX(row);
        ASSERT_INDEX(col);
        return matrix_[row][col];
    }

    void update(const size_t row, const size_t col, const DataType& newValue) const
    {
        ASSERT_INDEX(row);
        ASSERT_INDEX(col);
        matrix_[row][col] = newValue;
    }

private:
    mutable std::vector<std::vector<DataType>> matrix_;
};

template <typename DataType>
using CopyableMatrix = Matrix<DataType, ENABLE_MOVE, ENABLE_COPY>;

template <typename DataType>
using NonCopyableMatrix = Matrix<DataType, ENABLE_MOVE, DISABLE_COPY>;

} // namespace src::Structures
