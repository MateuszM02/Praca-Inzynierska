#pragma once

#include "Concepts.hpp"
#include "../MethodType.hpp"

#include <chrono> // mierzenie czasu wykonania testu
#include <iostream>
#include <vector>

#include <boost/range/algorithm/merge.hpp> // boost::range::merge

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
struct VectorStruct final
{
    using DataVector = std::vector<Mergeable<DataType>>;

    VectorStruct(
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

template <typename DataType>
class Merger final
{

using DataVector = std::vector<Mergeable<DataType>>;

public:
    Merger(VectorStruct<DataType> vectors)
    : v1_(std::move(vectors.v1_))
    , v2_(std::move(vectors.v2_))
    , expectedResult_(std::move(vectors.expectedResult_))
    { }

    DataVector callMerger(const MethodType& methodType, std::ostream& os)
    {
        switch (methodType)
        {
            case MethodType::STL:
                return measureExecutionTime(&mergeSTL, "STL", os);
            case MethodType::Boost:
                return measureExecutionTime(&mergeBoost, "Boost", os);
            case MethodType::Simple:
                return measureExecutionTime(&mergeSimple, "Simple", os);
            default:
                throw new std::invalid_argument("Zly typ metody!");
        }
    }

private:
    DataVector measureExecutionTime(
        DataVector(Merger::*memberFunction)(),
        const std::string& methodName,
        std::ostream& os)
    {
        auto start = std::chrono::high_resolution_clock::now();
        DataVector result = (this->*memberFunction)();
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        os << methodName << " call time: " << duration.count() << " seconds\n";
        return result;
    }

    DataVector mergeSTL()
    {
        DataVector resultVec;
        resultVec.resize(expectedResult_.size());
        std::merge(v1_.begin(), v1_.end(), v2_.begin(), v2_.end(), resultVec.begin());
        return resultVec;
    }

    DataVector mergeBoost()
    {
        DataVector resultVec;
        resultVec.resize(expectedResult_.size());
        boost::range::merge(v1_, v2_, resultVec.begin());
        return resultVec;
    }

    DataVector mergeSimple()
    {
        const unsigned int size1 = v1_.size();
        const unsigned int size2 = v2_.size();

        DataVector resultVec;
        resultVec.resize(expectedResult_.size());
        unsigned int index1 = 0;
        unsigned int index2 = 0;

        while (index1 < size1 && index2 < size2)
        {
            if (v1_[index1] < v2_[index2])
            {
                resultVec[index1+index2] = v1_[index1];
                index1++;
            }
            else
            {
                resultVec[index1+index2] = v2_[index2];
                index2++;
            }
        }
        while (index1 < size1)
        {
            resultVec[index1+index2] = v1_[index1];
            index1++;
        }
        while (index2 < size2)
        {
            resultVec[index1+index2] = v2_[index2];
            index2++;
        }
        return resultVec;
    }

public:
    DataVector v1_;
    DataVector v2_;
    DataVector expectedResult_;
};

} // namespace src::Algorithms
