#pragma once

#include "../SortTestFixture.hpp"
#include "../../../src/Structures/PointsImpl.hpp"

using namespace src::Structures;

namespace tests::Sort
{

struct PointsSortArgs final : public SortTestStruct<Point2D>
{
    explicit PointsSortArgs(Point2D (*f)(), const unsigned int n)
    : SortTestStruct<Point2D>(
        TestType::SortPoints,
        std::make_shared<Sorter<Point2D>>(initTestData<std::vector<Point2D>>(f, n)))
    { }

    PointsSortArgs(Point2D (*f)(const unsigned int), const unsigned int n)
    : SortTestStruct<Point2D>(
        TestType::SortPoints,
        std::make_shared<Sorter<Point2D>>(initTestData<std::vector<Point2D>>(f, n)))
    { }
};

class PointsSortFixture : public SortTestFixture<Point2D>
{
public:
    static Point2D sortedGenerator(const unsigned int i)
    {
        return Point2D(i, i);
    }

    static Point2D reverseSortedGenerator(const unsigned int i)
    {
        return Point2D(UINT32_MAX - i, UINT32_MAX - i);
    }

    static Point2D randomGenerator()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<unsigned int> dis(0, UINT32_MAX);

        unsigned int x = dis(gen);
        unsigned int y = dis(gen);
        return Point2D(x, y);
    }
};

TEST_P(PointsSortFixture, pointsSortTest)
{
    VerifyTest(GetParam());
}

} // namespace tests::Sort
