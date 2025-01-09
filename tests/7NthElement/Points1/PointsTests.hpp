#pragma once

#include "../NthElementTestFixture.hpp"
#include "../../../src/Structures/PointsImpl.hpp"

using namespace src::Structures;

namespace tests::NthElement
{

struct PointsNthElementArgs final : public NthElementTestStruct<std::vector<Point2D>>
{
    explicit PointsNthElementArgs(
        Point2D (*fun)(const unsigned int),
        const unsigned int n,
        const unsigned int vectorSize)
    : NthElementTestStruct<std::vector<Point2D>>(
        TestType::NthElementPoints,
        std::make_shared<NthFinder<std::vector<Point2D>>>(initTestData7(fun, n, vectorSize)))
    { }
};

class PointsNthElementFixture : public NthElementTestFixture<std::vector<Point2D>>
{
public:
    static Point2D fmod3i3_mod7i64(const unsigned int i)
    {
        return Point2D(3*i + (i % 3), 7*i % 64);
    }

    static Point2D f3i_mod9i64(const unsigned int i)
    {
        return Point2D(3*i, 9*i % 64);
    }
};

TEST_P(PointsNthElementFixture, PointsNthElementTest)
{
    VerifyTestCustomFor7(GetParam());
}

} // namespace tests::NthElement
