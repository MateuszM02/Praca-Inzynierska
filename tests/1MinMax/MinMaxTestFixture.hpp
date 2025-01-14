#pragma once

#include "../../src/Algorithms/MinMaxFinder.hpp"
#include "../../src/Structures/CustomPairImpl.hpp"
#include "../BaseTestFixture.hpp"

#include <random>

using namespace src::Algorithms;

namespace tests::MinMax
{
template <typename Container, typename ResultType>
struct MinMaxTestStruct : public BaseTestStruct<ResultType>
{
protected:
    explicit MinMaxTestStruct(const TestType testType,
        Callback<MinMaxFinder<Container>>&& callback)
    : BaseTestStruct<ResultType>(testType, std::move(callback))
    { }
};

// Klasa abstrakcyjna MinMaxTestFixture, po ktorej dziedzicza klasy testowe metod MinMax
template <typename DataType>
class MinMaxTestFixture : public BaseTestFixture<CopyablePair<DataType>>
{
protected:
    MinMaxTestFixture() = default;

    void VerifyTestCustomFor1(const std::shared_ptr<BaseTestStruct<CopyablePair<DataType>>>& args)
    {
        using namespace std::placeholders;
        auto checker = std::bind(&MinMaxTestFixture::verifyCustomFor1, this, _1, _2, _3, _4);
        this->VerifyTest(args, checker);
    }

private:
    void verifyCustomFor1(
        const CopyablePair<DataType>& stlResult,
        const CopyablePair<DataType>& boostResult,
        const CopyablePair<DataType>& simpleResult,
        std::ostringstream& os)
    requires EqualityComparable<DataType>
    {
        EXPECT_EQ_OS(stlResult, boostResult, os) << "Wyniki STL i Boost roznia sie";
        EXPECT_EQ_OS(stlResult, simpleResult, os) << "Wyniki STL i Simple roznia sie";
        EXPECT_EQ_OS(boostResult, simpleResult, os) << "Wyniki Boost i Simple roznia sie";
    }
};

using MinMaxUIntTestFixture = MinMaxTestFixture<unsigned int>;

} // namespace tests::MinMax
