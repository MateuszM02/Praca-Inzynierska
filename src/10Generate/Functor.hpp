#pragma once
#include "../MethodType.hpp"

#include <algorithm> // std::generate
#include <array>
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

    std::vector<DataType> call(const unsigned int n, const MethodType& methodType)
    {
        switch (methodType)
        {
            case MethodType::STL:
                return generateSTL(n);
            case MethodType::Boost:
                return generateBoost(n);
            case MethodType::Simple:
                return generateSimple(n);
            default:
                throw new std::invalid_argument("Zly typ metody!");
        }
    }

private:
    std::vector<DataType> generateSTL(const unsigned int n) 
    {
        return {};
        
        // TODO: naprawic SEGFAULT rzucany przez operator()()
        // std::vector<DataType> sequence(n);
        // std::generate(sequence.begin(), sequence.end(), std::ref(*this));
        // return sequence;
    }

    std::vector<DataType> generateBoost(const unsigned int n) 
    {
        return {};
        
        // TODO: naprawic SEGFAULT rzucany przez operator()()
        // std::vector<DataType> sequence(n);
        // boost::range::generate(sequence, std::ref(*this));
        // return sequence;
    }

    std::vector<DataType> generateSimple(const unsigned int n) 
    {
        return {};

        // TODO: naprawic SEGFAULT rzucany przez operator()()
        // std::vector<DataType> sequence(n);
        // for (DataType& element : sequence)
        // {
        //     element = this->operator()();
        // }
        // return sequence;
    }
};
} // namespace src::Generate
