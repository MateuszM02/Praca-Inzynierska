#pragma once

#include "../Concepts.hpp"

namespace src::Algorithms
{

// Klasa rozszerzajaca dowolny typ tak, aby dalo sie go porownywac
template <typename DataType>
class Mergeable final
{
    public:
    // Konstruktor domyslny aby dzialaly testy
    Mergeable()
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
    , copyAssignFunc_(
        [](DataType&, const DataType&) -> void
        {
            throw std::invalid_argument("This default method should never be called!");
        })
    { } 
    
    // Konstruktor dla typow nieporownywalnych
    Mergeable(DataType data,
        bool (*eqFunc)(const DataType&, const DataType&),
        bool (*lessFunc)(const DataType&, const DataType&),
        void (*copyAssignFunc)(DataType&, const DataType&))
    : data_(std::move(data))
    , eqFunc_(eqFunc)
    , lessFunc_(lessFunc)
    , copyAssignFunc_(copyAssignFunc)
    { } 
    
    // Konstruktor dla typow, ktore spelniaja koncept Comparable
    Mergeable(DataType data)
    requires Comparable<DataType>
    : data_(std::move(data))
    , eqFunc_([](const DataType& lhs, const DataType& rhs) { return lhs == rhs; })
    , lessFunc_([](const DataType& lhs, const DataType& rhs) { return lhs < rhs; })
    , copyAssignFunc_([](DataType& dest, const DataType& src) { dest = src; })
    { } 
    
    // Operator przypisania kopiujacego
    Mergeable& operator=(const Mergeable& other)
    {
        if (this != &other)
        {
            eqFunc_ = other.eqFunc_;
            lessFunc_ = other.lessFunc_;
            copyAssignFunc_ = other.copyAssignFunc_;
            copyAssignFunc_(data_, other.data_);
        }
        return *this;
    }
    
    bool operator==(const Mergeable& other) const
    {
        return eqFunc_(data_, other.data_);
    }
    
    bool operator<(const Mergeable& other) const
    {
        return lessFunc_(data_, other.data_);
    }
    
private:
    DataType data_;
    bool (*eqFunc_)(const DataType&, const DataType&);
    bool (*lessFunc_)(const DataType&, const DataType&);
    void (*copyAssignFunc_)(DataType&, const DataType&);
};

template <typename DataType>
struct MergerData final
{
    using DataVector = std::vector<Mergeable<DataType>>;

    MergerData(
        DataVector vec1,
        DataVector vec2,
        DataVector result)
    : v1_{std::move(vec1)}
    , v2_{std::move(vec2)}
    , expectedResult_{std::move(result)}
    { }

    DataVector v1_;
    DataVector v2_;
    DataVector expectedResult_;
};

} // namespace src::Algorithms