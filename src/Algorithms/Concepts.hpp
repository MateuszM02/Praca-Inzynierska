#pragma once
#include <concepts> // concept (C++ 20)

namespace src::Algorithms
{

// typ pozwalajacy na dodawanie za pomoca operatora+ (nie musi posiadac operatora+= ale moze)
template <typename DataType>
concept Addable = requires(DataType a, DataType b)
{
    { a + b } -> std::convertible_to<DataType>;
};

// typ pozwalajacy na mnozenie za pomoca operatora*= (nie musi posiadac operatora* ale moze)
template <typename DataType>
concept Multiplicable = requires(DataType a, DataType b)
{
    { a *= b } -> std::convertible_to<DataType&>;
};

// Typ elementow przy scalaniu wektorow musi miec nastepujace operatory
// = przypisania - aby mozna bylo elementy wektorow wejsciowych przypisac do wektora wynikowego bez tworzenia kopii
// == rownosci - aby sprawdzic, czy poprawnie scalilismy 2 wektory w testach
// < mniejszosci - domyslny comparator std::merge i boost::range::merge
template <typename DataType>
concept Comparable = requires(DataType a, DataType b)
{
    { a == b } -> std::convertible_to<bool>;
    { a < b } -> std::convertible_to<bool>;
} && std::is_copy_assignable_v<DataType>;

} // namespace src::Algorithms
