#pragma once

#include "../src/Algorithms/Base.hpp"
#include "../src/Concepts/DataTypeConcepts.hpp"
#include "Path.hpp"

#include <fstream>

#include <gtest/gtest.h>

using namespace src::Algorithms;
using namespace src::Concepts;

#define EXPECT_EQ_OS(val1, val2, os) \
    if (not ((val1) == (val2))) \
    { \
        os << "Wartosc " #val1 " rozni sie od wartosci " #val2 ".\n"; \
        if constexpr (Printable<decltype(val1)> && Printable<decltype(val2)>) \
        { \
            os << "Wartosc " #val1 ":\n"; \
            os << val1; \
            os << "\nWartosc " #val2 ":\n"; \
            os << val2; \
            os << "\n--------------------------------------------------\n"; \
        } \
    } \
    EXPECT_EQ(val1, val2)

namespace tests
{

template <typename GivenReturnType, typename ExpectedReturnType>
using IsOfType = std::enable_if_t<std::is_same_v<GivenReturnType, ExpectedReturnType>>;

template <typename Type>
using Callback = std::function<std::shared_ptr<Type>()>;

template <typename ResultType>
struct BaseTestStruct
{
protected:
    explicit BaseTestStruct(const TestType testType,
        Callback<BaseClass<ResultType>>&& callback)
    : filePath_{Path::Create(testType)}
    , callback_{std::move(callback)}
    { }

    // tylko przenoszenie
    BaseTestStruct(BaseTestStruct&&) = default;
    BaseTestStruct& operator=(BaseTestStruct&&) = default;
    BaseTestStruct(const BaseTestStruct&) = delete;
    BaseTestStruct& operator=(const BaseTestStruct&) = delete;

    // Do wypisywania nazwy klasy w testach
    friend std::ostream& operator<<(std::ostream& os, const BaseTestStruct& instance)
    {
        os << "[obiekt klasy " << typeid(instance).name() << "]";
        return os;
    }

    template <typename Container, typename = IsOfType<Container, std::vector<typename Container::value_type>>>
    static std::vector<typename Container::value_type>
    initTestData(typename Container::value_type (*generator)(), const unsigned int n)
    {
        std::vector<typename Container::value_type> v;
        v.reserve(n);

        for (unsigned int i = 1; i <= n; ++i)
        {
            v.emplace_back(generator());
        }
        return v;
    }

    template <typename Container, typename = IsOfType<Container, std::set<typename Container::value_type>>>
    static std::set<typename Container::value_type>
    initTestData(typename Container::value_type (*generator)(const unsigned int), const unsigned int n)
    {
        std::set<typename Container::value_type> v;
        for (unsigned int i = 1; i <= n; ++i)
        {
            v.insert(generator(i));
        }
        return v;
    }

    template <typename Container, typename = IsOfType<Container, std::vector<typename Container::value_type>>>
    static std::vector<typename Container::value_type>
    initTestData(typename Container::value_type (*generator)(const unsigned int), const unsigned int n)
    {
        std::vector<typename Container::value_type> v;
        v.reserve(n);

        for (unsigned int i = 1; i <= n; ++i)
        {
            v.emplace_back(generator(i));
        }
        return v;
    }

    template <typename Container, typename = IsOfType<Container, std::vector<typename Container::value_type>>>
    static std::vector<typename Container::value_type>
    initTestData(typename Container::value_type (*generator)(const unsigned int), const TestPair& info)
    {
        std::vector<typename Container::value_type> v;
        v.reserve(info.first);

        for (unsigned int i = 1; i <= info.first; ++i)
        {
            v.emplace_back(generator(info.second));
        }
        return v;
    }

public:
    // Zdobadz wartosc danego pola obiektu trzymanego przez callback_
    template <typename FieldType, typename Derived>
    FieldType getField(FieldType Derived::*field) const
    {
        static_assert(std::is_base_of_v<BaseClass<ResultType>, Derived>,
            "Derived must be derived from BaseClass<ResultType>");

        std::shared_ptr<BaseClass<ResultType>> ref_ = getTestData();
        using ptrType = decltype(ref_.get());

        static_assert(std::is_pointer_v<ptrType>, "callback_ must be a pointer");
        static_assert(std::is_convertible_v<ptrType, BaseClass<ResultType>*>,
            "callback_ must be convertible to BaseClass<ResultType>*");

        return static_cast<Derived*>(ref_.get())->*field;
    }

    std::string getFilePath() const { return filePath_; }

    std::shared_ptr<BaseClass<ResultType>> getTestData() const
    {
        if (!testData_.has_value())
            testData_ = callback_();
        return testData_.value();
    }

private:
    std::string filePath_;
    Callback<BaseClass<ResultType>> callback_;
    mutable std::optional<std::shared_ptr<BaseClass<ResultType>>> testData_;
};

// Klasa abstrakcyjna BaseTestFixture, po ktorej dziedzicza klasy testowe
template <typename ResultType>
class BaseTestFixture : public ::testing::TestWithParam<std::shared_ptr<BaseTestStruct<ResultType>>>
{
protected:
    BaseTestFixture() = default;

    // tylko przenoszenie
    BaseTestFixture(BaseTestFixture&&) = default;
    BaseTestFixture& operator=(BaseTestFixture&&) = default;
    BaseTestFixture(const BaseTestFixture&) = delete;
    BaseTestFixture& operator=(const BaseTestFixture&) = delete;

    void VerifyTest(const std::shared_ptr<BaseTestStruct<ResultType>>& args)
    {
        using namespace std::placeholders;
        auto checker = std::bind(&BaseTestFixture::verifyElementEqualities, this, _1, _2, _3, _4);
        VerifyTest(args, checker);
    }

    void VerifyTest(const std::shared_ptr<BaseTestStruct<ResultType>>& args,
        const std::function<void(const ResultType&, const ResultType&,
            const ResultType&, std::ostringstream&)>& checker)
    {
        std::ostringstream os; // Uzycie ostringstream do wypisywania wynikow testow

        const std::shared_ptr<BaseClass<ResultType>>& testData = args->getTestData();
        const auto& [stlResult, boostResult, simpleResult] = testData->callEachWithTimer(os);

        // Zapisywanie wynikow testu do pliku
        std::ofstream outFile(args->getFilePath(), std::ios::out | std::ios::trunc);
        if (outFile.is_open())
        {
            checker(stlResult, boostResult, simpleResult, os);
            outFile << os.str();
            outFile.close();
        }
        else
        {
            std::cerr << "Nie udalo sie zapisac wynikow testu do pliku: " << args->getFilePath() << "\n";
        }
    }

private:
    void verifyElementEqualities(
        const ResultType& stlResult,
        const ResultType& boostResult,
        const ResultType& simpleResult,
        std::ostringstream& os) const
    requires EqualityComparable<typename ResultType::value_type>
    {
        ::testing::internal::CaptureStdout(),
        ::testing::internal::CaptureStderr();

        EXPECT_EQ_OS(stlResult.size(), simpleResult.size(), os);
        EXPECT_EQ_OS(boostResult.size(), simpleResult.size(), os);

        if (::testing::Test::HasFailure())  return;

        auto stlIter = stlResult.begin();
        auto boostIter = boostResult.begin();
        auto simpleIter = simpleResult.begin();
        unsigned int i = 0;

        while (simpleIter != simpleResult.end())
        {
            EXPECT_EQ_OS(*stlIter, *simpleIter, os) << "Wynik STL rozni sie na indeksie " << i;
            EXPECT_EQ_OS(*boostIter, *simpleIter, os) << "Wynik Boost rozni sie na indeksie " << i;

            ++i;
            ++stlIter;
            ++boostIter;
            ++simpleIter;
        }
    }
};

template <typename Base, typename TestArgsStructure, typename... Args>
void createTestArgs(
    std::vector<std::shared_ptr<Base>>& testArgs,
    const std::vector<unsigned int>& testSizes,
    const Args&... args)
{
    for (const unsigned int testSize : testSizes)
    {
        testArgs.emplace_back(
            std::make_shared<TestArgsStructure>(args..., testSize));
    }
}

template <typename Base, typename TestArgsStructure, typename... Args>
void createTestArgs(
    std::vector<std::shared_ptr<Base>>& testArgs,
    const std::vector<TestPair>& testSizePairs,
    const Args&... args)
{
    for (const TestPair& testSizePair : testSizePairs)
    {
        testArgs.emplace_back(
            std::make_shared<TestArgsStructure>(args..., testSizePair));
    }
}

} // namespace tests
