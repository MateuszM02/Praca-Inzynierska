#pragma once
#include "../MergeTestFixture.hpp"
#include "../../Path.hpp"
#include "../../../src/3Merge/Points1/Points.hpp"

#include <functional>
#include <random>

namespace tests::Merge::Points1tests
{

struct PointsArgs : public MergeTestStruct<Points1::Point2D>
{
    PointsArgs(
        const std::string& path,
        const VectorStruct<Points1::Point2D>& vectors);
};

class PointsFixture : public MergeTestFixture<Points1::Point2D>
{
public:
    static VectorStruct<Points1::Point2D> initPoints(
        std::function<Points1::Point2D(int)> fun1,
        std::function<Points1::Point2D(int)> fun2, 
        const int n1,
        const int n2)
    {
        std::vector<Points1::Point2D> v1;
        std::vector<Points1::Point2D> v2;
        std::vector<Points1::Point2D> expectedResult;
        v1.reserve(n1);
        v2.reserve(n2);
        expectedResult.reserve(n1 + n2);

        for (int i = 0; i < n1; ++i)
        {
            v1.push_back(fun1(i));
        }
        for (int i = 0; i < n2; ++i)
        {
            v2.push_back(fun2(i));
        }

        int x1 = 0;
        int x2 = 0;
        Points1::Point2D p1 = fun1(x1);
        Points1::Point2D p2 = fun2(x2);

        while (x1 < n1 && x2 < n2)
        {
            if (p1 < p2)
            {
                expectedResult.push_back(p1);
                p1 = fun1(++x1);
            }
            else
            {
                expectedResult.push_back(p2);
                p2 = fun2(++x2);
            }
        }
        while (x1 < n1)
        {
            expectedResult.push_back(p1);
            p1 = fun1(++x1);
        }
        while (x2 < n2)
        {
            expectedResult.push_back(p2);
            p2 = fun2(++x2);
        }

        return { v1, v2, expectedResult };
    }

    static Points1::Point2D fmod3i3_mod7i64(int i)
    {
        return { 3*i + (i % 3), 7*i % 64 };
    }

    static Points1::Point2D f3i_mod9i64(int i)
    {
        return { 3*i, 9*i % 64 };
    }
};

TEST_P(PointsFixture, pointsTest)
{ 
    VerifyTest(GetParam());
}

} // namespace tests::Merge::Points1tests
