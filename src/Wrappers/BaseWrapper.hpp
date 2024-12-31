#pragma once

#include <functional>
#include <type_traits>
#include <vector>

#define ENABLE_MOVE true
#define DISABLE_MOVE false
#define ENABLE_COPY true
#define DISABLE_COPY false

namespace src::Wrappers
{

template <typename DataType, bool EnableMove = false, bool EnableCopy = false>
class BaseWrapper
{
protected:
    BaseWrapper(const DataType& data)
    : storedValue_(data) { }

    template <typename std::enable_if<EnableCopy, bool>::type = true>
    BaseWrapper(const BaseWrapper& other)
    {
        auto thisFieldList = getClassFields();
        const auto otherFieldList = other.getClassFields();
        for (size_t i = 0; i < thisFieldList.size(); ++i)
        {
            *thisFieldList[i] = *otherFieldList[i];
        }
    }

    template <typename std::enable_if<EnableMove, bool>::type = true>
    BaseWrapper(BaseWrapper&& other)
    {
        auto thisFieldList = getClassFields();
        const auto otherFieldList = other.getClassFields();
        for (size_t i = 0; i < thisFieldList.size(); ++i)
        {
            *thisFieldList[i] = std::move(*otherFieldList[i]);
        }
    }

    template <typename std::enable_if<EnableCopy, bool>::type = true>
    BaseWrapper& operator=(const BaseWrapper& other)
    {
        auto thisFieldList = getClassFields();
        const auto otherFieldList = other.getClassFields();
        for (size_t i = 0; i < thisFieldList.size(); ++i)
        {
            *thisFieldList[i] = *otherFieldList[i];
        }
        return *this;
    }

    template <typename std::enable_if<EnableMove, bool>::type = true>
    BaseWrapper& operator=(BaseWrapper&& other)
    {
        auto thisFieldList = getClassFields();
        const auto otherFieldList = other.getClassFields();
        for (size_t i = 0; i < thisFieldList.size(); ++i)
        {
            *thisFieldList[i] = std::move(*otherFieldList[i]);
        }
        return *this;
    }

    void setValue(const DataType& newValue) { storedValue_ = std::move(newValue); }

    virtual std::vector<void*> getClassFields() = 0;

public:
    DataType getValue() const { return storedValue_; }

private:
    DataType storedValue_;
};

} // namespace src::Wrappers
