#pragma once

#include "../Concepts/DataTypeConcepts.hpp"
#include "BaseWrapper.hpp"

#include <functional>

namespace src::Wrappers
{

// Klasa rozszerzajaca dowolny typ tak, aby dalo sie dynamicznie nadpisywac jego operator+
template <typename DataType>
class AddableWrapper : virtual public BaseWrapper<DataType>
{
public:
    AddableWrapper(DataType data,
        std::function<DataType(const DataType&, const DataType&)> add)
    : BaseWrapper<DataType>(std::move(data))
    , add_(std::move(add))
    { }
    
    AddableWrapper operator+(const AddableWrapper& other) const
    {
        return AddableWrapper<DataType>(
            add_(this->getValue(), other.getValue()),
            add_);
    }

protected:
    std::function<DataType(const DataType&, const DataType&)> add_;
};

} // namespace src::Wrappers
