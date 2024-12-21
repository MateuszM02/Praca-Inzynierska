#pragma once

#include "../MethodType.hpp"

#include <chrono> // mierzenie czasu wykonania testu
#include <vector>

namespace src::Algorithms
{

template <typename DataType, typename Container = std::vector<DataType>>
class BaseClass
{
public:
    virtual ~BaseClass() = default;
    BaseClass() = default;
    
    Container call(const MethodType& methodType, std::ostream& os)
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
    
protected:
    virtual void resetData() = 0;
    virtual Container executeSTL() = 0;
    virtual Container executeBoost() = 0;
    virtual Container executeSimple() = 0;

private:
    Container measureExecutionTime(
        Container(BaseClass::*memberFunction)(),
        const std::string& methodName,
        std::ostream& os)
    {
        auto start = std::chrono::high_resolution_clock::now();
        Container result = (this->*memberFunction)();
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        os << methodName << " call time: " << duration.count() << " seconds\n";
        
        resetData();
        return result;
    }
};

} // namespace src::Algorithms
