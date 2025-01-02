#pragma once

#include <any>
#include <vector>
#include <type_traits> // std::enable_if

#define ENABLE_MOVE true
#define DISABLE_MOVE false
#define ENABLE_COPY true
#define DISABLE_COPY false

namespace src::Structures
{

template <bool EnableMove, bool EnableCopy>
class BaseWrapper
{
public:
    explicit BaseWrapper(const std::vector<std::any>& classFields)
    : classFields_(classFields) 
    { }

    template <typename std::enable_if<EnableCopy, int>::type = 0>
    BaseWrapper(const BaseWrapper& other)
    : classFields_(other.classFields_)
    {
        copyFields(other);
    }

    template <typename std::enable_if<EnableMove, int>::type = 0>
    BaseWrapper(BaseWrapper&& other) noexcept
    : classFields_(std::move(other.classFields_))
    {
        moveFields(std::move(other));
    }

    template <typename std::enable_if<EnableCopy, int>::type = 0>
    BaseWrapper& operator=(const BaseWrapper& other)
    {
        if (this != &other)
        {
            classFields_ = other.classFields_;
            copyFields(other);
        }
        return *this;
    }

    template <typename std::enable_if<EnableMove, int>::type = 0>
    BaseWrapper& operator=(BaseWrapper&& other) noexcept {
        if (this != &other)
        {
            classFields_ = std::move(other.classFields_);
            moveFields(std::move(other));
        }
        return *this;
    }

private:
    std::vector<std::any> classFields_;

    void copyFields(const BaseWrapper& other)
    {
        for (size_t i = 0; i < classFields_.size(); ++i)
        {
            if (classFields_[i].has_value() && other.classFields_[i].has_value())
                classFields_[i] = other.classFields_[i];
        }
    }

    void moveFields(BaseWrapper&& other) {
        for (size_t i = 0; i < classFields_.size(); ++i)
        {
            if (classFields_[i].has_value() && other.classFields_[i].has_value())
                classFields_[i] = std::move(other.classFields_[i]);
        }
    }
};

} // namespace src::Structures


// #pragma once

// #include <any>
// #include <vector>
// #include <type_traits> // std::enable_if

// #define ENABLE_MOVE true
// #define DISABLE_MOVE false
// #define ENABLE_COPY true
// #define DISABLE_COPY false

// namespace src::Structures
// {

// template <bool EnableMove, bool EnableCopy>
// class BaseWrapper
// {
// public:
//     BaseWrapper(const std::vector<std::any>& classFields)
//     : classFields_(classFields) 
//     { }

//     template <bool E = EnableCopy, typename std::enable_if<E, int>::type = 0>
//     BaseWrapper(const BaseWrapper& other)
//     : classFields_(other.classFields_)
//     {
//         copyFields(other);
//     }

//     template <bool E = EnableMove, typename std::enable_if<E, int>::type = 0>
//     BaseWrapper(BaseWrapper&& other) noexcept
//     : classFields_(std::move(other.classFields_))
//     {
//         moveFields(std::move(other));
//     }

//     template <bool E = EnableCopy, typename std::enable_if<E, int>::type = 0>
//     BaseWrapper& operator=(const BaseWrapper& other)
//     {
//         if (this != &other)
//         {
//             classFields_ = other.classFields_;
//             copyFields(other);
//         }
//         return *this;
//     }

//     template <bool E = EnableMove, typename std::enable_if<E, int>::type = 0>
//     BaseWrapper& operator=(BaseWrapper&& other) noexcept {
//         if (this != &other)
//         {
//             classFields_ = std::move(other.classFields_);
//             moveFields(std::move(other));
//         }
//         return *this;
//     }

// private:
//     std::vector<std::any> classFields_;

//     void copyFields(const BaseWrapper& other)
//     {
//         for (size_t i = 0; i < classFields_.size(); ++i)
//         {
//             if (classFields_[i].has_value() && other.classFields_[i].has_value())
//                 classFields_[i] = other.classFields_[i];
//         }
//     }

//     void moveFields(BaseWrapper&& other) {
//         for (size_t i = 0; i < classFields_.size(); ++i)
//         {
//             if (classFields_[i].has_value() && other.classFields_[i].has_value())
//                 classFields_[i] = std::move(other.classFields_[i]);
//         }
//     }
// };

// } // namespace src::Structures
