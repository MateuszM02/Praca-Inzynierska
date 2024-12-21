#pragma once

#include "DataTypeConcepts.hpp"

namespace src::Concepts
{

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

// Koncept sprawdzajacy, czy kontener nadaje sie do std::nth_element
template <typename Container> concept NthElementCompatible =
    Iterable<Container> &&
    CopyComparable<typename Container::value_type> &&
    Swappable<typename Container::value_type>;

// Koncept sprawdzajacy, czy kontener nadaje sie do boost::remove_erase_if
template <typename Container>
concept Removable = Iterable<Container> && Erasable<Container>;

} // namespace src::Concepts
