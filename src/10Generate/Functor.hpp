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

    std::vector<DataType> call(const unsigned int n, const MethodType& methodType)
    {
        switch (methodType)
        {
            case MethodType::STL:
                return measureExecutionTime("STL", &generateSTL, n);
            case MethodType::Boost:
                return measureExecutionTime("Boost", &generateBoost, n);
            case MethodType::Simple:
                return measureExecutionTime("Simple", &generateSimple, n);
            default:
                throw new std::invalid_argument("Zly typ metody!");
        }
    }

private:
    std::vector<DataType> measureExecutionTime(
        const std::string& methodName, 
        std::vector<DataType>(Functor::*memberFunction)(const unsigned int), 
        const unsigned int n) 
    { 
        auto start = std::chrono::high_resolution_clock::now(); 
        std::vector<DataType> result = (this->*memberFunction)(n); 
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start; 
        std::cout << methodName << " call time: " << duration.count() << " seconds\n"; 
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
