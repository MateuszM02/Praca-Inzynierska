#pragma once

namespace src::Wrappers
{

template <typename DataType>
class BaseWrapper
{
protected:
    BaseWrapper(const DataType data)
    : storedValue_(std::move(data))
    { }

    void setValue(const DataType& newValue) { storedValue_ = std::move(newValue); }

public:
    DataType getValue() const { return storedValue_; }

private:
    DataType storedValue_;
};

} // namespace src::Wrappers
