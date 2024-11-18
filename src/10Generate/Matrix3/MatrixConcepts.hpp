#pragma once
#include "../Functor.hpp"

namespace src::Generate::Matrix3
{
// Koncept sprawdzajacy, czy typ macierzy ma metode size() zwracajaca std::size_t 
template<typename MaybeSquareMatrix> 
concept HasSizeMethod = requires(const MaybeSquareMatrix& matrix) 
{ 
    { matrix.size() } -> std::same_as<std::size_t>;
};

// Koncept sprawdzajacy, czy macierz jest dwuwymiarowa struktura z co najmniej 1 liczbowym elementem
template<typename MaybeSquareMatrix> 
concept IsNestedContainer = requires(const MaybeSquareMatrix& matrix) 
{
    { matrix[0][0] }; // sprawdza, czy da sie zdobyc wartosci elementu za pomoca operatora[]
    requires std::is_arithmetic_v<decltype(matrix[0][0])>; // sprawdza, czy ten element jest liczba
};

template <typename MaybeSquareMatrix>
bool isSquareMatrix(const MaybeSquareMatrix& m) 
{
    std::size_t size = m.size();
    for (const auto& row : m) 
    {
        if (row.size() != size) 
        {
            return false;
        }
    }
    return true;
}

// Koncept sprawdzajacy, czy macierz jest kwadratowa
template<typename MaybeSquareMatrix> 
concept IsSquareMatrix = 
    HasSizeMethod<MaybeSquareMatrix> && 
    IsNestedContainer<MaybeSquareMatrix> && 
    requires(const MaybeSquareMatrix& m) 
{
    { isSquareMatrix(m) } -> std::same_as<bool>;
};
} // namespace src::Generate::Matrix3
