#pragma once

#include <concepts> // concept (C++ 20)
#include <limits> // std::numeric_limits

namespace src::Concepts
{

// Sprawdza, czy typ nadaje sie do 2Accumulable
template <typename DataType>
concept HasNumericLimits = std::numeric_limits<DataType>::is_specialized &&
    requires()
{
    { std::numeric_limits<DataType>::min() } -> std::same_as<DataType>;
    { std::numeric_limits<DataType>::max() } -> std::same_as<DataType>;
    { std::numeric_limits<DataType>::lowest() } -> std::same_as<DataType>;
    { std::numeric_limits<DataType>::epsilon() } -> std::same_as<DataType>;
};

// typ pozwalajacy na dodawanie za pomoca operatora+ (nie musi posiadac operatora+= ale moze)
template <typename DataType>
concept Addable = requires(DataType a, DataType b)
{
    { a + b } -> std::same_as<DataType>;
};

// typ pozwalajacy na dzielenie przez stala za pomoca operatora/ (nie musi posiadac operatora/= ale moze)
template <typename DataType>
concept DivisibleByConst = requires(DataType a, unsigned int div)
{
    { a / div } -> std::same_as<DataType>;
};

// typ pozwalajacy na mnozenie za pomoca operatora* (nie musi posiadac operatora*= ale moze)
template <typename DataType>
concept Multiplicable = requires(DataType a, DataType b)
{
    { a * b } -> std::same_as<DataType>;
};

// typ pozwalajacy na dodawanie za pomoca operatora+= (nie musi posiadac operatora+ ale moze)
template <typename DataType>
concept NoCopyAddable = requires(DataType a, DataType b)
{
    { a += b } -> std::same_as<DataType&>;
};

} // namespace src::Concepts
