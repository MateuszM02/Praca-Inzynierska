#pragma once

#include "../src/Algorithms/Base.hpp"
#include "../src/Concepts/DataTypeConcepts.hpp"
#include "Path.hpp"

#include <fstream>
#include <unordered_map>

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
            os << "Wartosc " #val2 ":\n"; \
            os << val2; \
            os << "--------------------------------------------------\n"; \
        } \
    } \
    EXPECT_EQ(val1, val2)

namespace tests
{

template <typename Container>
struct BaseTestStruct
{
protected:
    explicit BaseTestStruct(const TestType testType,
        std::shared_ptr<BaseClass<Container>>&& f)
    : filePath_{createPath(testType)}
    , ref_{std::move(f)}
    { }

protected:
    template <typename DataType>
    requires std::is_move_constructible_v<DataType>
    static std::vector<DataType>
    initTestData(DataType (*generator)()&, const unsigned int n)
    {
        std::vector<DataType> v;
        v.reserve(n);

        for (unsigned int i = 1; i <= n; ++i)
        {
            v.emplace_back(generator());
        }
        return v;
    }
    
    template <typename DataType>
    requires std::is_move_constructible_v<DataType>
    static std::vector<DataType>
    initTestData(DataType (*generator)(const unsigned int)&, const unsigned int n)
    {
        std::vector<DataType> v;
        v.reserve(n);

        for (unsigned int i = 1; i <= n; ++i)
        {
            v.emplace_back(generator(i));
        }
        return v;
    }

public:
    // Zdobadz wartosc danego pola obiektu trzymanego przez ref_
    template <typename FieldType, typename Derived>
    FieldType getField(FieldType Derived::*field) const
    {
        static_assert(std::is_base_of_v<BaseClass<Container>, Derived>,
            "Derived must be derived from BaseClass<Container>");
        using ptrType = decltype(ref_.get());
        static_assert(std::is_pointer_v<ptrType>, "ref_ must be a pointer");
        static_assert(std::is_convertible_v<ptrType, BaseClass<Container>*>,
            "ref_ must be convertible to BaseClass<Container>*");

        return static_cast<Derived*>(ref_.get())->*field;
    }

private:
    std::string createPath(const TestType testType) const
    {
        static std::unordered_map<TestType, unsigned int> testIdMap;
        return Path::Create(testType, ++testIdMap[testType]);
    }

    const std::string filePath_;
    const std::shared_ptr<BaseClass<Container>> ref_;

    template <typename>
    friend class BaseTestFixture;
};

// Klasa abstrakcyjna BaseTestFixture, po ktorej dziedzicza klasy testowe metod generate
template <typename Container> 
class BaseTestFixture : public ::testing::TestWithParam<BaseTestStruct<Container>>
{
protected:
    BaseTestFixture() = default;

    void VerifyTest(const BaseTestStruct<Container>& args)
    {
        using namespace std::placeholders;
        auto checker = std::bind(&BaseTestFixture::verifyElementEqualities, this, _1, _2, _3, _4);
        VerifyTest(args, checker);
    }

    void VerifyTest(const BaseTestStruct<Container>& args,
        const std::function<void(const Container&, const Container&,
            const Container&, std::ostringstream&)>& checker)
    {
        std::ostringstream os; // Uzycie ostringstream do wypisywania wynikow testow

        const Container& stlResult = args.ref_->call(src::MethodType::STL, os);
        const Container& boostResult = args.ref_->call(src::MethodType::Boost, os);
        const Container& simpleResult = args.ref_->call(src::MethodType::Simple, os);

        // Zapisywanie wynikow testu do pliku
        std::ofstream outFile(args.filePath_, std::ios::out | std::ios::trunc);
        if (outFile.is_open())
        {
            checker(stlResult, boostResult, simpleResult, os);
            outFile << os.str();
            outFile.close();
        }
        else
        {
            std::cerr << "Nie udalo sie zapisac wynikow testu do pliku: " << args.filePath_ << "\n";
        }
    }

private:
    void verifyElementEqualities(
        const Container& stlResult,
        const Container& boostResult,
        const Container& simpleResult,
        std::ostringstream& os) const
    requires EqualityComparable<typename Container::value_type>
    {
        ::testing::internal::CaptureStdout(),
        ::testing::internal::CaptureStderr();

        EXPECT_EQ_OS(stlResult.size(), simpleResult.size(), os) << "Rozmiar wyniku STL rozni sie od oczekiwanego.";
        EXPECT_EQ_OS(boostResult.size(), simpleResult.size(), os) << "Rozmiar wyniku Boost rozni sie od oczekiwanego.";

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

} // namespace tests
