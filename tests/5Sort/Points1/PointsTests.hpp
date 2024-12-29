#pragma once

#include "../SortTestFixture.hpp"
#include "../../../src/Structures/PointsImpl.hpp"

using namespace src::Structures;
using namespace src::Wrappers;

namespace tests::Sort
{

struct PointsSortArgs : public SortTestStruct<Point2D>
{
    PointsSortArgs(
        ComparableWrapper<Point2D> (*f)(const unsigned int),
        const unsigned int n)
    : SortTestStruct<Point2D>(
        SortPoints,
        std::make_shared<Sorter<Point2D>>(
            SortTestFixture<Point2D>::initTestData(f, n)))
    { }
};

class PointsSortFixture : public SortTestFixture<Point2D>
{
public:
    static ComparableWrapper<Point2D> sortedGenerator(const unsigned int i)
    {
        return { { i, i }, Point2DImpl::equal, Point2DImpl::less };
    }

    static ComparableWrapper<Point2D> reverseSortedGenerator(const unsigned int i)
    {
        return { { UINT32_MAX - i, UINT32_MAX - i }, Point2DImpl::equal, Point2DImpl::less };
    }

    static ComparableWrapper<Point2D> randomGenerator(const unsigned int i)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<unsigned int> dis(0, UINT32_MAX);
        
        unsigned int x = dis(gen);
        unsigned int y = dis(gen);
        return { { x, y }, Point2DImpl::equal, Point2DImpl::less };
    }
};

TEST_P(PointsSortFixture, pointsSortTest)
{ 
    VerifyTest(GetParam());
}

} // namespace tests::Sort
