#pragma once

#include "../../src/Algorithms/Accumulator.hpp"
#include "../BaseTestFixture.hpp"

using namespace src::Algorithms;

namespace tests::Accumulate
{

template <typename DataType>
using DataVector = std::vector<DataType>;

template <typename DataType>
struct AccumulateTestStruct : public BaseTestStruct<Accumulator<DataType>>
{
public:
    AccumulateTestStruct(
        const TestType testType,
        std::shared_ptr<Accumulator<DataType>> f)
    : BaseTestStruct<Accumulator<DataType>>(testType, std::move(f))
    { }
};

// Klasa abstrakcyjna AccumulateTestFixture, po ktorej dziedzicza klasy testowe metod Accumulate
template <typename DataType>
class AccumulateTestFixture : public BaseTestFixture<AccResults<DataType>, Accumulator<DataType>>
{
public:
    static DataVector<DataType> initTestData(
        DataType (*f)(const unsigned int),
        const unsigned int n)
    {
        DataVector<DataType> v;
        v.reserve(n);

        for (unsigned int i = 1; i <= n; ++i)
        {
            v.emplace_back(std::move(f(i)));
        }
        return v;
    }

    void VerifyTestCustomFor2(const BaseTestStruct<Accumulator<DataType>>& args)
    {
        using namespace std::placeholders;
        auto checker = std::bind(&AccumulateTestFixture::verifyCustomFor2, this, _1, _2, _3, _4);
        this->VerifyTest(args, checker);
    }

private:
    void verifyCustomFor2(
        const AccResults<DataType>& stlResult,
        const AccResults<DataType>& boostResult,
        const AccResults<DataType>& simpleResult,
        std::ostringstream& os)
    {
        EXPECT_EQ_OS(stlResult.sum, boostResult.sum, os) << "Sumy STL i Boost roznia sie";
        EXPECT_EQ_OS(stlResult.sum, simpleResult.sum, os) << "Sumy STL i Simple roznia sie";
        EXPECT_EQ_OS(boostResult.sum, simpleResult.sum, os) << "Sumy Boost i Simple roznia sie";

        EXPECT_EQ_OS(stlResult.minimum, boostResult.minimum, os) << "Minima STL i Boost roznia sie";
        EXPECT_EQ_OS(stlResult.minimum, simpleResult.minimum, os) << "Minima STL i Simple roznia sie";
        EXPECT_EQ_OS(boostResult.minimum, simpleResult.minimum, os) << "Minima Boost i Simple roznia sie";

        EXPECT_EQ_OS(stlResult.maximum, boostResult.maximum, os) << "Maxima STL i Boost roznia sie";
        EXPECT_EQ_OS(stlResult.maximum, simpleResult.maximum, os) << "Maxima STL i Simple roznia sie";
        EXPECT_EQ_OS(boostResult.maximum, simpleResult.maximum, os) << "Maxima Boost i Simple roznia sie";

        EXPECT_EQ_OS(stlResult.mean, boostResult.mean, os) << "Srednie STL i Boost roznia sie";
        EXPECT_EQ_OS(stlResult.mean, simpleResult.mean, os) << "Srednie STL i Simple roznia sie";
        EXPECT_EQ_OS(boostResult.mean, simpleResult.mean, os) << "Srednie Boost i Simple roznia sie";
    }
};

} // namespace tests::Accumulate
