#pragma once

#include "../Concepts/DataTypeConcepts.hpp"
#include "BaseWrapper.hpp"

#include <limits>

using namespace src::Concepts;

namespace src::Wrappers
{

// ComparableWrapper rozbudowany o operatory potrzebne do testow accumulate
template <typename DataType>
class AccumulableWrapper final : public BaseWrapper<DataType, ENABLE_MOVE, ENABLE_COPY>
{
public:
    // potrzebne jako poczatkowa wartosc std::accumulate
    AccumulableWrapper()
    requires Addable<DataType> && Comparable<DataType>
    : BaseWrapper<DataType, ENABLE_MOVE, ENABLE_COPY>(DataType())
    , add_(std::plus<DataType>())
    , equal_(std::equal_to<DataType>())
    , less_(std::less<DataType>())
    { }

    AccumulableWrapper(const DataType& data,
        std::function<DataType(const DataType&, const DataType&)> add,
        std::function<bool(const DataType&, const DataType&)> equal,
        std::function<bool(const DataType&, const DataType&)> less)
    : BaseWrapper<DataType, ENABLE_MOVE, ENABLE_COPY>(data)
    , add_(std::move(add))
    , equal_(std::move(equal))
    , less_(std::move(less))
    { }

    // suma wszystkich elementow
    AccumulableWrapper operator+(const AccumulableWrapper& other) const
    {
        return AccumulableWrapper<DataType>(
            add_(this->getValue(), other.getValue()),
            add_, equal_, less_);
    }

    // minimalny/maksymalny element
    bool operator==(const AccumulableWrapper& other) const
    {
        return equal_(this->getValue(), other.getValue());
    }

    // minimalny/maksymalny element
    bool operator<(const AccumulableWrapper& other) const
    {
        return less_(this->getValue(), other.getValue());
    }

    // boost::accumulator_set - tagi sum & mean
    bool operator>(const AccumulableWrapper& other) const
    {
        return  !less_(this->getValue(), other.getValue()) && 
                !equal_(this->getValue(), other.getValue());
    }

    // boost::accumulator_set - tagi sum & mean
    AccumulableWrapper& operator+=(const AccumulableWrapper& other)
    {
        this->setValue(add_(this->getValue(), other.getValue()));
        return *this;
    }

    // boost::accumulator_set - tagi sum & mean
    AccumulableWrapper operator/(const long long unsigned int x) const
    {
        return AccumulableWrapper<DataType>(
            static_cast<double>(this->getValue()) / x,
            add_, equal_, less_);
    }

protected:
    std::function<DataType(const DataType&, const DataType&)> add_;
    std::function<bool(const DataType&, const DataType&)> equal_;
    std::function<bool(const DataType&, const DataType&)> less_;

    std::vector<void*> getClassFields() override
    {
        return { &add_, &equal_, &less_};
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

    static src::Wrappers::AccumulableWrapper<DataType> min()
    {
        return src::Wrappers::AccumulableWrapper<DataType>(
            std::numeric_limits<DataType>::min(),
            std::plus<DataType>(),
            std::equal_to<DataType>(),
            std::less<DataType>());
    }
    
    static src::Wrappers::AccumulableWrapper<DataType> max()
    {
        return src::Wrappers::AccumulableWrapper<DataType>(
            std::numeric_limits<DataType>::max(),
            std::plus<DataType>(),
            std::equal_to<DataType>(),
            std::less<DataType>());
    }
    
    static src::Wrappers::AccumulableWrapper<DataType> lowest()
    {
        return src::Wrappers::AccumulableWrapper<DataType>(
            std::numeric_limits<DataType>::lowest(),
            std::plus<DataType>(),
            std::equal_to<DataType>(),
            std::less<DataType>());
    }
};

} // namespace std
