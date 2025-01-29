#pragma once

#include <chrono> // mierzenie czasu wykonania testu

namespace src::Algorithms
{

template <typename ResultType>
using Results = std::tuple<ResultType, ResultType, ResultType>;

using TestPair = std::pair<unsigned int, unsigned int>;

template <typename ResultType>
class BaseClass
{
public:
    Results<ResultType> callEachWithTimer(std::ostringstream& os) const
    {
        ResultType stlResult = measureExecutionTime(&BaseClass::executeSTL, "STL", os);
        resetData();
        ResultType boostResult = measureExecutionTime(&BaseClass::executeBoost, "Boost", os);
        resetData();
        ResultType simpleResult = measureExecutionTime(&BaseClass::executeSimple, "Simple", os);
        return std::make_tuple(std::move(stlResult), std::move(boostResult), std::move(simpleResult));
    }

    Results<ResultType> callEach() const
    {
        ResultType stlResult = executeSTL();
        resetData();
        ResultType boostResult = executeBoost();
        resetData();
        ResultType simpleResult = executeSimple();
        return Results(std::move(stlResult), std::move(boostResult), std::move(simpleResult));
    }

protected:
    BaseClass() = default;

    // tylko przenoszenie
    BaseClass(BaseClass&&) = default;
    BaseClass& operator=(BaseClass&&) = default;
    BaseClass(const BaseClass&) = delete;
    BaseClass& operator=(const BaseClass&) = delete;

    virtual ~BaseClass() = default;
    virtual void resetData() const = 0;
    virtual ResultType executeSTL() const = 0;
    virtual ResultType executeBoost() const = 0;
    virtual ResultType executeSimple() const = 0;

private:
    ResultType measureExecutionTime(
        ResultType(BaseClass::*memberFunction)() const,
        const std::string&,// methodName,
        std::ostringstream& os) const
    {
        const auto start = std::chrono::high_resolution_clock::now();
        ResultType result = (this->*memberFunction)();
        const auto end = std::chrono::high_resolution_clock::now();

        const std::chrono::duration<double> duration = end - start;
        os << duration.count() << "\t";

        return std::move(result);
    }
};

} // namespace src::Algorithms
