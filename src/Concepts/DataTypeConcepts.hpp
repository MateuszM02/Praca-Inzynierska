#pragma once

#include <iostream>
#include <ranges>
#include <vector>

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

// Koncept sprawdzajacy, czy typ ma operator ==
template <typename DataType>
concept EqualityComparable = requires(DataType a, DataType b)
{
    { a == b } -> std::same_as<bool>;
};

// Koncept sprawdzajacy, czy typ ma operatory ==, <, >
template <typename DataType>
concept Comparable = EqualityComparable<DataType> &&
    requires(DataType a, DataType b)
{
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

// Concept sprawdzajacy, czy typ spelnia warunki do 5Transformer
template <typename DataType>
concept Transformable = 
    (std::copyable<DataType> || std::movable<DataType>) &&
    std::ranges::range<std::vector<DataType>>;

} // namespace src::Concepts
