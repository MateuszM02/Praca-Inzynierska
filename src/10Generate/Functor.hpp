#pragma once
#include "../MethodType.hpp"

#include <algorithm> // std::generate
#include <array>
#include <chrono> // mierzenie czasu wykonania testu
#include <concepts> // concept (C++ 20)
#include <iostream>
#include <vector>

#include <boost/range/algorithm/generate.hpp> // boost::range::generate

namespace src::Generate
{
// Klasa abstrakcyjna Functor, po ktorej dziedzicza klasy funktorowe
template <class DataType> 
class Functor 
{ 
public: 
    virtual ~Functor() = default;
    virtual DataType operator()() = 0;
    virtual std::shared_ptr<Functor<DataType>> clone() const = 0;

    std::vector<DataType> callFunctor(
        const unsigned int n, 
        const MethodType& methodType,
        std::ostream& os)
    {
        switch (methodType)
        {
            case MethodType::STL:
                return measureExecutionTime(&generateSTL, "STL", n, os);
            case MethodType::Boost:
                return measureExecutionTime(&generateBoost, "Boost", n, os);
            case MethodType::Simple:
                return measureExecutionTime(&generateSimple, "Simple", n, os);
            default:
                throw new std::invalid_argument("Zly typ metody!");
        }
    }

private:
    std::vector<DataType> measureExecutionTime(
        std::vector<DataType>(Functor::*memberFunction)(const unsigned int),
        const std::string& methodName,
        const unsigned int n,
        std::ostream& os)
    { 
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<DataType> result = (this->*memberFunction)(n);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        os << methodName << " call time: " << duration.count() << " seconds\n";
        return result;
    }

    std::vector<DataType> generateSTL(const unsigned int n)
    {
        std::vector<DataType> sequence(n);
        std::generate(sequence.begin(), sequence.end(), [this]() { return this->operator()(); });
        return sequence;
    }

    std::vector<DataType> generateBoost(const unsigned int n)
    {
        std::vector<DataType> sequence(n);
        boost::range::generate(sequence, [this]() { return this->operator()(); });
        return sequence;
    }

    std::vector<DataType> generateSimple(const unsigned int n)
    {
        std::vector<DataType> sequence(n);
        for (DataType& element : sequence)
        {
            element = this->operator()();
        }
        return sequence;
    }
};

} // namespace src::Generate
