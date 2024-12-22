#pragma once

#include "../../Concepts/ContainerConcepts.hpp"

#include <vector>

using namespace src::Concepts;

namespace src::Algorithms
{

// Klasa rozszerzajaca dowolny typ tak, aby dalo sie go porownywac i zamieniac pozycja z innymi
template <typename DataType>
class Findable final
{
public:
    // Konstruktor domyslny aby dzialaly testy
    Findable()
    : data_(DataType())
    , eqFunc_(
        [](const DataType&, const DataType&) -> bool
        {
            throw std::invalid_argument("This default method should never be called!");
        })
    , lessFunc_(
        [](const DataType&, const DataType&) -> bool
        {
            throw std::invalid_argument("This default method should never be called!");
        })
    { }
    
    // Konstruktor dla typow nieporownywalnych
    Findable(DataType data,
        bool (*eqFunc)(const DataType&, const DataType&),
        bool (*lessFunc)(const DataType&, const DataType&),
        void (*copyAssignFunc)(DataType&, const DataType&))
    : data_(std::move(data))
    , eqFunc_(eqFunc)
    , lessFunc_(lessFunc)
    { }
    
    // Konstruktor dla typow, ktore spelniaja koncept CopyComparable
    Findable(DataType data)
    requires CopyComparable<DataType>
    : data_(std::move(data))
    , eqFunc_([](const DataType& lhs, const DataType& rhs) { return lhs == rhs; })
    , lessFunc_([](const DataType& lhs, const DataType& rhs) { return lhs < rhs; })
    { }
    
    bool operator==(const Findable& other) const
    {
        return eqFunc_(data_, other.data_);
    }
    
    bool operator<(const Findable& other) const
    {
        return lessFunc_(data_, other.data_);
    }
    
private:
    DataType data_;
    bool (*eqFunc_)(const DataType&, const DataType&);
    bool (*lessFunc_)(const DataType&, const DataType&);
};

template <typename DataType, NthElementCompatible Container = std::vector<Findable<DataType>>>
struct NthFinderData final
{
    NthFinderData(Container elements, const unsigned int n)
    : elements_{std::move(elements)}
    , n_{n}
    { }

    const Container elements_;
    const unsigned int n_;
};

} // namespace src::Algorithms
