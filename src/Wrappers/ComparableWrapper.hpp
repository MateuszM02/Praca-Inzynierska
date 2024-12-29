#pragma once

#include "../Concepts/DataTypeConcepts.hpp"
#include "BaseWrapper.hpp"

#include <functional>

namespace src::Wrappers
{

// Klasa rozszerzajaca dowolny typ tak, aby dalo sie dynamicznie nadpisywac jego operatory< oraz ==
template <typename DataType>
requires std::is_move_assignable_v<DataType> &&
         std::is_copy_assignable_v<DataType> &&
         std::is_move_constructible_v<DataType>
class ComparableWrapper : virtual public BaseWrapper<DataType>
{
public:
    ComparableWrapper(DataType data,
        std::function<bool(const DataType&, const DataType&)> equal,
        std::function<bool(const DataType&, const DataType&)> less)
    : BaseWrapper<DataType>(std::move(data))
    , equal_(std::move(equal))
    , less_(std::move(less))
    { }

    // Przypisanie przenoszace (potrzebne przy std::swap)
    ComparableWrapper& operator=(ComparableWrapper&& other)
    {
        if (this != &other)
        {
            this->setValue(other.getValue());
            this->equal_ = std::move(other.equal_);
            this->less_ = std::move(other.less_);
        }
        return *this;
    }

    // Konstruktor kopiujacy (potrzebny do naiwnego nth_element::partition)
    ComparableWrapper(const ComparableWrapper& other)
    : BaseWrapper<DataType>(other.getValue())
    , equal_(other.equal_)
    , less_(other.less_)
    { }

    // Przypisanie kopiujace (potrzebne do resetData)
    ComparableWrapper& operator=(const ComparableWrapper& other)
    {
        if (this != &other)
        {
            this->setValue(other.getValue());
            this->equal_ = other.equal_;
            this->less_ = other.less_;
        }
        return *this;
    }
    
    // Operatory
    bool operator==(const ComparableWrapper& other) const
    {
        return equal_(this->getValue(), other.getValue());
    }

    bool operator<(const ComparableWrapper& other) const
    {
        return less_(this->getValue(), other.getValue());
    }

protected:
    std::function<bool(const DataType&, const DataType&)> equal_;
    std::function<bool(const DataType&, const DataType&)> less_;
};

} // namespace src::Wrappers
