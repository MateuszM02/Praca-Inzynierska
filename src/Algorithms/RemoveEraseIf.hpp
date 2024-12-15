#pragma once

#include "Concepts.hpp"
#include "../MethodType.hpp"

#include <chrono> // mierzenie czasu wykonania testu
#include <iostream>
#include <vector>

#include <boost/range/algorithm_ext/erase.hpp> // boost::range::remove_erase_if

namespace src::Algorithms
{

template <typename DataType, typename Container = std::vector<DataType>>
struct RemoveEraseIfData final
{
    RemoveEraseIfData(
        Container elements,
        Container expectedResult,
        bool (*predicate)(const DataType&))
    : elements_{std::move(elements)}
    , expectedResult_{std::move(expectedResult)}
    , predicate_{predicate}
    { }

    Container elements_;
    Container expectedResult_;
    bool (*predicate_)(const DataType&);
};

template <typename DataType, Removable Container = std::vector<DataType>>
class Remover final
{
public:
    Remover(RemoveEraseIfData<DataType> data)
    : elements_(data.elements_)
    , initialElements_(std::move(data.elements_))
    , expectedResult_(std::move(data.expectedResult_))
    , predicate_(data.predicate_)
    { }

    Container callRemover(const MethodType& methodType, std::ostream& os)
    {
        switch (methodType)
        {
            case MethodType::STL:
                return measureExecutionTime(&RemoveEraseIfSTL, "STL", os);
            case MethodType::Boost:
                return measureExecutionTime(&RemoveEraseIfBoost, "Boost", os);
            case MethodType::Simple:
                return measureExecutionTime(&RemoveEraseIfSimple, "Simple", os);
            default:
                throw new std::invalid_argument("Zly typ metody!");
        }
    }

private:
    Container measureExecutionTime(
        Container(Remover::*memberFunction)(),
        const std::string& methodName,
        std::ostream& os)
    {
        auto start = std::chrono::high_resolution_clock::now();
        Container result = (this->*memberFunction)();
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        os << methodName << " call time: " << duration.count() << " seconds\n";
        this->elements_ = this->initialElements_;
        return result;
    }

    Container RemoveEraseIfSTL()
    {
        elements_.erase(
            std::remove_if(elements_.begin(), elements_.end(), predicate_),
            elements_.end());
        return elements_;
    }

    Container RemoveEraseIfBoost()
    {
        boost::range::remove_erase_if(elements_, predicate_);
        return elements_;
    }

    Container RemoveEraseIfSimple()
    {
        auto first = elements_.begin();
        for (auto current = elements_.begin(); current != elements_.end(); ++current)
        {
            if (!predicate_(*current))
            {
                if (first != current)
                {
                    *first = std::move(*current);
                }
                ++first;
            }
        }
        elements_.erase(first, elements_.end());
        return elements_;
    }

public:
    Container elements_;
    const Container initialElements_;
    const Container expectedResult_;
    bool (*predicate_)(const DataType&);
};

} // namespace src::Algorithms
