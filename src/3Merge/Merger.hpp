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
// == rownosci - aby sprawdzic, czy poprawnie scalilismy 2 wektory w testach
// < mniejszosci - domyslny comparator std::merge i boost::range::merge
template <typename DataType> 
concept Comparable = requires(DataType a, DataType b)
{
    { a == b } -> std::convertible_to<bool>;
    { a < b } -> std::convertible_to<bool>;
};

// Klasa abstrakcyjna Merger, po ktorej dziedzicza klasy przykladowe
template <Comparable DataType>
class Merger
{
public:
    Merger(const std::vector<DataType>& v1, const std::vector<DataType>& v2)
    : vec1{v1}
    , vec2{v2}
    { }

    virtual ~Merger() = default;

    std::vector<DataType> callMerger(const MethodType& methodType, std::ostream& os)
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

protected:
    const std::vector<DataType> vec1;
    const std::vector<DataType> vec2;

private:
    std::vector<DataType> measureExecutionTime(
        std::vector<DataType>(Merger::*memberFunction)(),
        const std::string& methodName,
        std::ostream& os)
    {
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<DataType> result = (this->*memberFunction)();
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        os << methodName << " call time: " << duration.count() << " seconds\n";
        return result;
    }

    std::vector<DataType> mergeSTL()
    {
        std::vector<DataType> resultVec(vec1.size()+vec2.size());
        std::merge(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), resultVec.begin());
        return resultVec;
    }

    std::vector<DataType> mergeBoost()
    {
        std::vector<DataType> resultVec(vec1.size()+vec2.size());
        boost::range::merge(vec1, vec2, resultVec.begin());
        return resultVec;
    }

    std::vector<DataType> mergeSimple()
    {
        const unsigned int size1 = vec1.size();
        const unsigned int size2 = vec2.size();

        std::vector<DataType> resultVec(size1 + size2);
        unsigned int index1 = 0;
        unsigned int index2 = 0;

        while (index1 < size1 && index2 < size2)
        {
            if (vec1[index1] < vec2[index2])
            {
                resultVec[index1+index2] = vec1[index1];
                index1++;
            }
            else
            {
                resultVec[index1+index2] = vec2[index2];
                index2++;
            }
        }
        while (index1 < size1)
        {
            resultVec[index1+index2] = vec1[index1];
            index1++;
        }
        while (index2 < size2)
        {
            resultVec[index1+index2] = vec2[index2];
            index2++;
        }
        return resultVec;
    }
};

} // namespace src::Merge
