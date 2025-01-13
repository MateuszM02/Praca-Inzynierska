#pragma once

#include "../../src/Algorithms/MinMaxFinder.hpp"
#include "../../src/Structures/PointsImpl.hpp"
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
template <typename DataType = unsigned int>
class MinMaxTestFixture : public BaseTestFixture<Point2D<DataType>>
{
protected:
    MinMaxTestFixture() = default;

    void VerifyTestCustomFor1(const std::shared_ptr<BaseTestStruct<Point2D<DataType>>>& args)
    {
        using namespace std::placeholders;
        auto checker = std::bind(&MinMaxTestFixture::verifyCustomFor1, this, _1, _2, _3, _4);
        this->VerifyTest(args, checker);
    }

private:
    void verifyCustomFor1(
        const Point2D<DataType>& stlResult,
        const Point2D<DataType>& boostResult,
        const Point2D<DataType>& simpleResult,
        std::ostringstream& os)
    requires EqualityComparable<DataType>
    {
        EXPECT_EQ_OS(stlResult, boostResult, os) << "Wyniki STL i Boost roznia sie";
        EXPECT_EQ_OS(stlResult, simpleResult, os) << "Wyniki STL i Simple roznia sie";
        EXPECT_EQ_OS(boostResult, simpleResult, os) << "Wyniki Boost i Simple roznia sie";
    }
};

} // namespace tests::MinMax
