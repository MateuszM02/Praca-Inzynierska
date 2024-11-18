#pragma once
#include <algorithm> // std::generate
#include <array>
#include <concepts> // concept (C++ 20)
#include <iostream>
#include <type_traits> // std::enable_if (C++ 11)
#include <vector>

#include <boost/range/algorithm/generate.hpp> // boost::range::generate

#include "../MethodType.hpp"

namespace src::RepeatFun
{
// Klasa abstrakcyjna Functor, po ktorej dziedzicza klasy funktorowe
template <class DataType> 
class Functor 
{ 
public: 
    virtual ~Functor() = default;
    virtual DataType operator()() = 0;

    std::vector<DataType> call(const unsigned int n, const MethodType& methodType)
    {
        switch (methodType)
        {
            case MethodType::STL:
                return generateSTL(*this, n);
            case MethodType::Boost:
                return generateBoost(*this, n);
            case MethodType::Simple:
                return generateSimple(*this, n);
            default:
                throw new std::invalid_argument("Zly typ metody!");
        }
    }

private:
    std::vector<DataType> generateSTL(Functor<DataType>& generator, const unsigned int n) 
    {
        std::vector<DataType> sequence;
        sequence.reserve(n);
        std::generate(sequence.begin(), sequence.end(), std::ref(generator));
        return sequence;
    }

    std::vector<DataType> generateBoost(Functor<DataType>& generator, const unsigned int n) 
    {
        std::vector<DataType> sequence;
        sequence.reserve(n);
        boost::range::generate(sequence, std::ref(generator));
        return sequence;
    }

    std::vector<DataType> generateSimple(Functor<DataType>& generator, const unsigned int n) 
    {
        std::vector<DataType> sequence;
        sequence.reserve(n);
        for (DataType& element : sequence)
        {
            element = generator();
        }
        return sequence;
    }
};
} // namespace src::RepeatFun
