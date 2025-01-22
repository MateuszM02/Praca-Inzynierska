#pragma once

#include <any>
#include <vector>

#define ENABLE_MOVE true
#define DISABLE_MOVE false
#define ENABLE_COPY true
#define DISABLE_COPY false

namespace src::Structures
{

template <bool EnableMove, bool EnableCopy> class BaseWrapper;

// Wersja 1/4 - brak przesuniecia i kopii ---------------------------------------------------------

template <>
class BaseWrapper<DISABLE_MOVE, DISABLE_COPY>
{
protected:
    explicit BaseWrapper(const std::vector<std::any>& classFields)
    : classFields_{classFields}
    { }

    BaseWrapper(BaseWrapper&& other) = delete;
    BaseWrapper& operator=(BaseWrapper&& other) = delete;
    BaseWrapper(const BaseWrapper& other) = delete;
    BaseWrapper& operator=(const BaseWrapper& other) = delete;

private:
    std::vector<std::any> classFields_;
};

// Wersja 2/4 - tylko przesuniecie ----------------------------------------------------------------

template <>
class BaseWrapper<ENABLE_MOVE, DISABLE_COPY>
{
protected:
    explicit BaseWrapper(const std::vector<std::any>& classFields)
    : classFields_{classFields}
    { }

    BaseWrapper(BaseWrapper&& other)
    : classFields_{other.classFields_}
    {
        for (size_t i = 0; i < classFields_.size(); ++i)
        {
            if (classFields_[i].has_value() && other.classFields_[i].has_value())
                classFields_[i] = std::move(other.classFields_[i]);
        }
    }

    BaseWrapper& operator=(BaseWrapper&& other)
    {
        if (this != &other)
        {
            classFields_ = other.classFields_;
            for (size_t i = 0; i < classFields_.size(); ++i)
            {
                if (classFields_[i].has_value() && other.classFields_[i].has_value())
                    classFields_[i] = std::move(other.classFields_[i]);
            }
        }
        return *this;
    }

    BaseWrapper(const BaseWrapper& other) = delete;
    BaseWrapper& operator=(const BaseWrapper& other) = delete;

private:
    std::vector<std::any> classFields_;
};

// Wersja 3/4 - tylko kopiowanie - jest niedozwolona ----------------------------------------------

template <>
class BaseWrapper<DISABLE_MOVE, ENABLE_COPY>
{
private:
    BaseWrapper() = delete;
};

// Wersja 4/4 - przenoszenie i kopiowanie ---------------------------------------------------------

template <>
class BaseWrapper<ENABLE_MOVE, ENABLE_COPY>
{
protected:
    explicit BaseWrapper(const std::vector<std::any>& classFields)
    : classFields_{classFields}
    { }

    BaseWrapper(BaseWrapper&& other)
    : classFields_{other.classFields_}
    {
        for (size_t i = 0; i < classFields_.size(); ++i)
        {
            if (classFields_[i].has_value() && other.classFields_[i].has_value())
                classFields_[i] = std::move(other.classFields_[i]);
        }
    }

    BaseWrapper& operator=(BaseWrapper&& other)
    {
        if (this != &other)
        {
            classFields_ = other.classFields_;
            for (size_t i = 0; i < classFields_.size(); ++i)
            {
                if (classFields_[i].has_value() && other.classFields_[i].has_value())
                    classFields_[i] = std::move(other.classFields_[i]);
            }
        }
        return *this;
    }

    BaseWrapper(const BaseWrapper& other)
    : classFields_{other.classFields_}
    {
        for (size_t i = 0; i < classFields_.size(); ++i)
        {
            if (classFields_[i].has_value() && other.classFields_[i].has_value())
                classFields_[i] = other.classFields_[i];
        }
    }

    BaseWrapper& operator=(const BaseWrapper& other)
    {
        if (this != &other)
        {
            classFields_ = other.classFields_;
            for (size_t i = 0; i < classFields_.size(); ++i)
            {
                if (classFields_[i].has_value() && other.classFields_[i].has_value())
                    classFields_[i] = other.classFields_[i];
            }
        }
        return *this;
    }

private:
    std::vector<std::any> classFields_;
};

} // namespace src::Structures
