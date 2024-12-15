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

// Koncept sprawdzajacy, czy kontener obsluguje iteracje
template <typename Container>
concept Iterable = requires(Container c)
{
    typename Container::iterator;
    { c.begin() } -> std::same_as<typename Container::iterator>;
    { c.end() } -> std::same_as<typename Container::iterator>;
};

// Koncept sprawdzajacy, czy kontener ma metode erase
template <typename Container>
concept Erasable = requires(Container c, typename Container::const_iterator it)
{
    { c.erase(it) } -> std::same_as<typename Container::iterator>;
    { c.erase(it, it) } -> std::same_as<typename Container::iterator>;
};

// Koncept sprawdzajacy, czy kontener nadaje sie do boost::remove_erase_if
template <typename Container>
concept Removable = Iterable<Container> && Erasable<Container>;

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
