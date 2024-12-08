#pragma once
#include "../MethodType.hpp"

#include <chrono> // mierzenie czasu wykonania testu
#include <concepts> // concept (C++ 20)
#include <iostream>
#include <vector>

#include <boost/range/algorithm/merge.hpp> // boost::range::merge

namespace src::Merge
{

// Typ elementow przy scalaniu wektorow musi miec nastepujace operatory
// = przypisania - aby mozna bylo elementy wektorow wejsciowych zapisac do wektora wynikowego
// == rownosci - aby sprawdzic, czy poprawnie scalilismy 2 wektory w testach
// < mniejszosci - domyslny comparator std::merge i boost::range::merge
template <typename DataType> 
concept Comparable = requires(DataType a, DataType b)
{
    { a = b } -> std::same_as<DataType&>;
    { a == b } -> std::convertible_to<bool>;
    { a < b } -> std::convertible_to<bool>;
};

// Klasa abstrakcyjna Merger, po ktorej dziedzicza klasy przykladowe
template <Comparable DataType>
class Merger
{
public:
    virtual ~Merger() = default;

    std::vector<DataType> callMerger(
        const MethodType& methodType, 
        const std::vector<DataType>& v1,
        const std::vector<DataType>& v2,
        std::ostream& os)
    {
        switch (methodType)
        {
            case MethodType::STL:
                return measureExecutionTime(&mergeSTL, "STL", v1, v2, os);
            case MethodType::Boost:
                return measureExecutionTime(&mergeBoost, "Boost", v1, v2, os);
            case MethodType::Simple:
                return measureExecutionTime(&mergeSimple, "Simple", v1, v2, os);
            default:
                throw new std::invalid_argument("Zly typ metody!");
        }
    }

private:
    std::vector<DataType> measureExecutionTime(
        std::vector<DataType>(Merger::*memberFunction)
            (const std::vector<DataType>&, const std::vector<DataType>&),
        const std::string& methodName,
        const std::vector<DataType>& v1,
        const std::vector<DataType>& v2,
        std::ostream& os)
    {
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<DataType> result = (this->*memberFunction)(v1, v2);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        os << methodName << " call time: " << duration.count() << " seconds\n";
        return result;
    }

    std::vector<DataType> mergeSTL(const std::vector<DataType>& v1, const std::vector<DataType>& v2)
    {
        std::vector<DataType> resultVec(v1.size() + v2.size());
        std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), resultVec.begin());
        return resultVec;
    }

    std::vector<DataType> mergeBoost(const std::vector<DataType>& v1, const std::vector<DataType>& v2)
    {
        std::vector<DataType> resultVec(v1.size() + v2.size());
        boost::range::merge(v1, v2, resultVec.begin());
        return resultVec;
    }

    std::vector<DataType> mergeSimple(const std::vector<DataType>& v1, const std::vector<DataType>& v2)
    {
        const unsigned int size1 = v1.size();
        const unsigned int size2 = v2.size();

        std::vector<DataType> resultVec(size1 + size2);
        unsigned int index1 = 0;
        unsigned int index2 = 0;

        while (index1 < size1 && index2 < size2)
        {
            if (v1[index1] < v2[index2])
            {
                resultVec[index1+index2] = v1[index1];
                index1++;
            }
            else
            {
                resultVec[index1+index2] = v2[index2];
                index2++;
            }
        }
        while (index1 < size1)
        {
            resultVec[index1+index2] = v1[index1];
            index1++;
        }
        while (index2 < size2)
        {
            resultVec[index1+index2] = v2[index2];
            index2++;
        }
        return resultVec;
    }
};

} // namespace src::Merge
