#pragma once

#include <iostream>

#include "MathConcepts.hpp"

namespace src::Concepts
{

// Koncept sprawdzajacy, czy da sie wypisac na ekranie wartosc elementu
template <typename DataType>
concept Printable = requires(DataType a, std::ostream& os)
{
    { os << a } -> std::convertible_to<std::ostream&>;
};

// Koncept sprawdzajacy, czy da sie zamienic 2 elementy
template <typename DataType>
concept Swappable = requires(DataType a, DataType b)
{
    { std::swap(a, b) } -> std::same_as<void>;
};

// Koncept sprawdzajacy, czy typ ma operatory ==, <, >
template <typename DataType>
concept Comparable = requires(DataType a, DataType b)
{
    { a == b } -> std::same_as<bool>;
    { a < b } -> std::same_as<bool>;
    { a > b } -> std::same_as<bool>;
};

// Sprawdza, czy typ nadaje sie do 2Accumulable
template <typename DataType>
concept IsAccumulable =
    HasNumericLimits<DataType> &&
    Addable<DataType> &&
    DivisibleByConst<DataType> &&
    NoCopyAddable<DataType> &&
    Comparable<DataType>;

} // namespace src::Concepts
