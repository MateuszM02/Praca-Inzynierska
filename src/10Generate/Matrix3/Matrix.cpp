#include "Matrix.hpp"

namespace src::Generate::Matrix3
{
template<typename SquareMatrix> 
requires IsSquareMatrix<SquareMatrix>
const auto& 
Matrix<SquareMatrix>::at(size_t i, size_t j) const
{ 
    if (i >= n || j >= n) 
    { 
        throw std::out_of_range("Index out of range."); 
    } 
    return matrix[i][j]; 
} 
 
template<typename SquareMatrix>
requires IsSquareMatrix<SquareMatrix>
Matrix<SquareMatrix> 
Matrix<SquareMatrix>::operator*(const Matrix<SquareMatrix>& other) const
{ 
    if (n != other.n) 
    { 
        throw std::invalid_argument("Matrix dimensions must match for multiplication."); 
    } 
    
    SquareMatrix result(matrix.size(), 
        typename SquareMatrix::value_type(matrix.size())); 
    
    for (size_t i = 0; i < n; ++i) 
    { 
        for (size_t j = 0; j < n; ++j) 
        { 
            result[i][j] = 0; 
            for (size_t k = 0; k < n; ++k) 
            { 
                result[i][j] += matrix[i][k] * other.matrix[k][j]; 
            } 
        } 
    } 
    return Matrix<SquareMatrix>(result);
}

template <typename OtherSquareMatrix>
requires IsSquareMatrix<OtherSquareMatrix>
std::ostream& 
operator<<(std::ostream& os, const Matrix<OtherSquareMatrix>& mat) 
{ 
    for (const auto& row : mat.matrix) 
    { 
        for (const auto& elem : row) 
        { 
            os << elem << " "; 
        } 
        os << std::endl; 
    } 
    return os; 
}

} // namespace src::Generate::Matrix3
