#pragma once

#include "../MergeTestFixture.hpp"
#include "../../../src/Structures/PointsImpl.hpp"

using namespace src::Structures;

namespace tests::Merge
{

struct PointsMergeArgs final : public MergeTestStruct<Point2D>
{
    explicit PointsMergeArgs(
        Point2D (*dataCreator1)(const unsigned int),
        Point2D (*dataCreator2)(const unsigned int),
        const unsigned int n1,
        const unsigned int n2)
    : MergeTestStruct<Point2D>(
        TestType::MergePoints,
        [dataCreator1, dataCreator2, n1, n2]()
        {
            return initTestData3(dataCreator1, dataCreator2, n1, n2);
        })
    { }
};

class PointsMergeFixture : public MergeTestFixture<Point2D>
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

TEST_P(PointsMergeFixture, PointsMergeTest)
{
    VerifyTest(GetParam());
}

} // namespace tests::Merge
