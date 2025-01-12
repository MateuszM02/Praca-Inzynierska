#pragma once

#include "../MethodType.hpp"

#include <chrono> // mierzenie czasu wykonania testu
#include <vector>

namespace src::Algorithms
{

template <typename Container>
class BaseClass
{
public:
    Container call(const MethodType& methodType, std::ostringstream& os) const
    {
        switch (methodType)
        {
            case MethodType::STL:
                return measureExecutionTime(&BaseClass::executeSTL, "STL", os);
            case MethodType::Boost:
                return measureExecutionTime(&BaseClass::executeBoost, "Boost", os);
            case MethodType::Simple:
                return measureExecutionTime(&BaseClass::executeSimple, "Simple", os);
            default: throw std::invalid_argument("Zły typ metody!");
        }
    }

    std::tuple<Container, Container, Container> callEach() const
    {
        const Container& stlResult = executeSTL();
        const Container& boostResult = executeBoost();
        const Container& simpleResult = executeSimple();
        return { stlResult, boostResult, simpleResult };
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
    virtual Container executeSTL() const = 0;
    virtual Container executeBoost() const = 0;
    virtual Container executeSimple() const = 0;

private:
    Container measureExecutionTime(
        Container(BaseClass::*memberFunction)() const,
        const std::string& methodName,
        std::ostringstream& os) const
    {
        const auto start = std::chrono::high_resolution_clock::now();
        const Container result = (this->*memberFunction)();
        const auto end = std::chrono::high_resolution_clock::now();

        const std::chrono::duration<double> duration = end - start;
        os << methodName << " call time: " << duration.count() << " seconds\n";

        resetData();
        return result;
    }
};

} // namespace src::Algorithms
