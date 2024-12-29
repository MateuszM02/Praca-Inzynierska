#pragma once

namespace src::Wrappers
{

template <typename DataType>
class BaseWrapper
{
public:
    BaseWrapper(DataType data)
    : storedValue_(std::move(data))
    { }

    DataType getValue() const { return storedValue_; }
    void setValue(const DataType& newValue) { storedValue_ = std::move(newValue); }

protected:
    DataType storedValue_;
};

} // namespace src::Wrappers
