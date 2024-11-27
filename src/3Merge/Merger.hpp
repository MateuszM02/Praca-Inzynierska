#pragma once
#include "../MethodType.hpp"

#include <concepts> // concept (C++ 20)
#include <iostream>
#include <vector>

#include <boost/range/algorithm/merge.hpp> // boost::range::merge

namespace src::Merge
{

// Klasa abstrakcyjna Merger, po ktorej dziedzicza klasy przykladowe
template <class DataType> 
class Merger
{
public: 
    virtual ~Merger() = default;
    // operator porownania < dla danego typu
    virtual bool operator()(const DataType& elem1, const DataType& elem2) = 0;

    std::vector<DataType> call(
        const std::vector<DataType>& v1, 
        const std::vector<DataType>& v2, 
        const MethodType& methodType)
        requires requires(const std::vector<DataType>& v1, const std::vector<DataType>& v2) 
        { 
            { v1.size() == v2.size() } -> std::convertible_to<bool>;
        }
    {
        switch (methodType)
        {
            case MethodType::STL:
                return mergeSTL(v1, v2);
            case MethodType::Boost:
                return mergeBoost(v1, v2);
            case MethodType::Simple:
                return mergeSimple(v1, v2);
            default:
                throw new std::invalid_argument("Zly typ metody!");
        }
    }

private:
    std::vector<DataType> mergeSTL(
        const std::vector<DataType>& v1, 
        const std::vector<DataType>& v2)
    {
        std::vector<DataType> sequence;
        sequence.reserve(v1.size());
        std::merge(v1.begin(), v2.begin(), v1.end(), v2.end(), sequence.begin(), std::ref(*this));
        return sequence;
    }

    std::vector<DataType> mergeBoost(
        const std::vector<DataType>& v1, 
        const std::vector<DataType>& v2)
    {
        std::vector<DataType> sequence;
        sequence.reserve(v1.size());
        boost::range::merge(v1, v2, sequence.begin(), std::ref(*this));
        return sequence;
    }

    std::vector<DataType> mergeSimple(
        const std::vector<DataType>& v1, 
        const std::vector<DataType>& v2)
    {
        std::vector<DataType> sequence;
        sequence.reserve(v1.size());
        unsigned int index1 = 0;
        unsigned int index2 = 0;
        const unsigned int size1 = v1.size();
        const unsigned int size2 = v2.size();

        while (index1 < size1 && index2 < size2)
        {
            if (this->operator()(v1[index1], v2[index2]))
            {
                sequence.emplace_back(v1[index1]);
                index1++;
            }
            else
            {
                sequence.emplace_back(v2[index2]);
                index2++;
            }
        }
        while (index1 < size1)
        {
            sequence.emplace_back(v1[index1]);
            index1++;
        }
        while (index2 < size2)
        {
            sequence.emplace_back(v2[index2]);
            index2++;
        }
        return sequence;
    }
};

} // namespace src::Merge
