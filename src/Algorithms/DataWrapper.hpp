#pragma once

#include <functional>

namespace src::Algorithms
{

// Klasa rozszerzajaca dowolny typ tak, aby dalo sie dynamicznie nadpisywac jego operatory
template <typename DataType>
requires std::is_move_assignable_v<DataType> &&
         std::is_copy_assignable_v<DataType> &&
         std::is_move_constructible_v<DataType>
class DataWrapper final
{
public:
    DataWrapper(DataType data,
        std::function<bool(const DataType&, const DataType&)> equal,
        std::function<bool(const DataType&, const DataType&)> less)
    : data_(std::move(data))
    , equal_(std::move(equal))
    , less_(std::move(less))
    { }

    // Przypisanie przenoszace (potrzebne przy std::swap)
    DataWrapper& operator=(DataWrapper&& other)
    {
        if (this != &other)
        {
            this->data_ = std::move(other.data_);
            this->equal_ = std::move(other.equal_);
            this->less_ = std::move(other.less_);
        }
        return *this;
    }

    // Konstruktor kopiujacy (potrzebny do naiwnego nth_element::partition)
    DataWrapper(const DataWrapper& other)
    : data_(other.data_)
    , equal_(other.equal_)
    , less_(other.less_)
    { }

    // Przypisanie kopiujace (potrzebne do resetData)
    DataWrapper& operator=(const DataWrapper& other)
    {
        if (this != &other)
        {
            this->data_ = other.data_;
            this->equal_ = other.equal_;
            this->less_ = other.less_;
        }
        return *this;
    }
    
    // Operatory
    bool operator==(const DataWrapper& other) const
    {
        return equal_(data_, other.data_);
    }

    bool operator<(const DataWrapper& other) const
    {
        return less_(data_, other.data_);
    }

private:
    DataType data_;
    std::function<bool(const DataType&, const DataType&)> equal_;
    std::function<bool(const DataType&, const DataType&)> less_;
};

} // namespace src::Algorithms
