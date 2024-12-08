#include "Matrix.hpp"

namespace src::Generate::Matrix3
{
template <class Number>
requires std::is_arithmetic_v<Number>
const auto& 
Matrix<Number>::at(size_t row, size_t col) const
{ 
    if (row >= n || col >= n) 
    { 
        throw std::out_of_range("Index out of range."); 
    } 
    return matrix[row][col]; 
} 
 
template <class Number>
requires std::is_arithmetic_v<Number>
Matrix<Number> 
Matrix<Number>::operator*=(const Matrix<Number>& other)
{ 
    if (n != other.n) 
    { 
        throw std::invalid_argument("Matrix dimensions must match for multiplication."); 
    } 
    
    SquareMatrix(Number) result(n, std::vector<Number>(n)); 

    for (size_t row = 0; row < n; ++row)
    {
        for (size_t col = 0; col < n; ++col)
        {
            result[row][col] = 0;
            for (size_t k = 0; k < n; ++k)
            {
                result[row][col] += matrix[row][k] * other.matrix[k][col];
            }
        }
    }

    // for (size_t row = 0; row < n; ++row)
    // {
    //     for (size_t col = 0; col < n; ++col)
    //     {
    //         matrix[row][col] = result[row][col];
    //     }
    // }
    matrix = result;
    return *this;
}

template <class Number>
requires std::is_arithmetic_v<Number>
bool 
Matrix<Number>::operator==(const Matrix<Number>& other) const
{
    if (this->n != other.n) return false;

    for (size_t row = 0; row < this->n; ++row)
    {
        for (size_t col = 0; col < this->n; ++col)
        {
            if (this->at(row, col) != other.at(row, col))
                return false;
        }
    }

    return true;
}

template <typename OtherNumber>
requires std::is_arithmetic_v<OtherNumber>
std::ostream& 
operator<<(std::ostream& os, const Matrix<OtherNumber>& mat) 
{ 
    for (size_t row = 0; row < mat.size(); ++row)
    {
        for (size_t col = 0; col < mat.size(); ++col)
        {
            os << mat.at(row, col) << " ";
        }
    }
    return os; 
}

// Jawna instancja klasy zeby dzialaly testy
template class Matrix<int>;
template class Matrix<double>;

template std::ostream& operator<< (std::ostream& os, const Matrix<int>& mat);
template std::ostream& operator<< (std::ostream& os, const Matrix<double>& mat);

} // namespace src::Generate::Matrix3
