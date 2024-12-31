#pragma once

#include "BaseWrapper.hpp"

namespace src::Wrappers
{

// Klasa rozszerzajaca dowolny typ tak, aby dalo sie dynamicznie nadpisywac jego operatory< oraz ==
template <typename DataType>
class ComparableWrapper final : public BaseWrapper<DataType, ENABLE_MOVE, ENABLE_COPY>
{
public:
    ComparableWrapper(const DataType& data,
        std::function<bool(const DataType&, const DataType&)> equal,
        std::function<bool(const DataType&, const DataType&)> less)
    : BaseWrapper<DataType, ENABLE_MOVE, ENABLE_COPY>(data)
    , equal_(std::move(equal))
    , less_(std::move(less))
    { }

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

    std::vector<void*> getClassFields() override
    {
        return { &equal_, &less_};
    }
};

} // namespace src::Wrappers
