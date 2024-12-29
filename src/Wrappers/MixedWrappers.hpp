#pragma once

#include "AddableWrapper.hpp"
#include "ComparableWrapper.hpp"

#include <limits>

using namespace src::Concepts;

namespace src::Wrappers
{

// ComparableWrapper rozbudowany o operatory potrzebne do testow accumulate
template <typename DataType>
class AccumulableWrapper final : public AddableWrapper<DataType>, public ComparableWrapper<DataType>
{
public:
    // potrzebne do accumulate
    AccumulableWrapper()
    requires Addable<DataType> && Comparable<DataType>
    : BaseWrapper<DataType>(DataType())
    , AddableWrapper<DataType>(DataType(), std::plus<DataType>())
    , ComparableWrapper<DataType>(DataType(), std::equal_to<DataType>(), std::less<DataType>())
    { }

    AccumulableWrapper(DataType data,
        std::function<DataType(const DataType&, const DataType&)> add,
        std::function<bool(const DataType&, const DataType&)> equal,
        std::function<bool(const DataType&, const DataType&)> less)
    : BaseWrapper<DataType>(std::move(data))
    , AddableWrapper<DataType>(DataType(), std::move(add))
    , ComparableWrapper<DataType>(DataType(), std::move(equal), std::move(less))
    { }

    // suma wszystkich elementow
    AccumulableWrapper operator+(const AccumulableWrapper& other) const
    {
        return AccumulableWrapper<DataType>(
            this->add_(this->getValue(), other.getValue()),
            this->add_,
            this->equal_,
            this->less_);
    }

    // boost::accumulator_set - tagi sum & mean
    bool operator>(const AccumulableWrapper& other) const
    {
        return !this->less_(this->getValue(), other.getValue()) && 
            !this->equal_(this->getValue(), other.getValue());
    }

    // boost::accumulator_set - tagi sum & mean
    AccumulableWrapper& operator+=(const AccumulableWrapper& other)
    {
        this->setValue(this->add_(this->getValue(), other.getValue()));
        return *this;
    }

    // boost::accumulator_set - tagi sum & mean
    AccumulableWrapper operator/(const long long unsigned int x) const
    {
        return AccumulableWrapper<DataType>(
            static_cast<double>(this->getValue()) / x,
            this->add_,
            this->equal_,
            this->less_);
    }
};

} // namespace src::Wrappers

namespace std
{

template <typename DataType>
class numeric_limits<src::Wrappers::AccumulableWrapper<DataType>>
{
public:
    static const bool is_specialized = true;


    static src::Wrappers::AccumulableWrapper<DataType> min() noexcept
    {
        return src::Wrappers::AccumulableWrapper<DataType>(
            std::numeric_limits<DataType>::min(),
            std::plus<DataType>(),
            std::equal_to<DataType>(),
            std::less<DataType>());
    }
    
    static src::Wrappers::AccumulableWrapper<DataType> max() noexcept
    {
        return src::Wrappers::AccumulableWrapper<DataType>(
            std::numeric_limits<DataType>::max(),
            std::plus<DataType>(),
            std::equal_to<DataType>(),
            std::less<DataType>());
    }
    
    static src::Wrappers::AccumulableWrapper<DataType> lowest() noexcept
    {
        return src::Wrappers::AccumulableWrapper<DataType>(
            std::numeric_limits<DataType>::lowest(),
            std::plus<DataType>(),
            std::equal_to<DataType>(),
            std::less<DataType>());
    }
};

} // namespace std
