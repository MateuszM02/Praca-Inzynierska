#pragma once
#include "../MergeTestFixture.hpp"
#include "../../Path.hpp"
#include "../../../src/3Merge/Vector3/IntVector.hpp"

#include <functional>
#include <random>

namespace tests::Merge::Vector3tests
{

struct IntVectorArgs : public MergeTestStruct<Vector3::IntVector>
{
    IntVectorArgs(
        const std::string& path,
        VectorStruct<Vector3::IntVector> vectors);
};

class IntVectorFixture : public MergeTestFixture<Vector3::IntVector>
{
public:
    static Vector3::IntVector f10i_imod7(const int n)
    {
        std::vector<int> v;
        v.reserve(n);
        for (unsigned int i = 0; i < n; ++i)
        {
            v.emplace_back(10*i + ((i+1) % 7));
        }
        Vector3::IntVector iv = { std::move(v) };
        return std::move(iv);
    }

    static Vector3::IntVector f10i_imod9(const int n)
    {
        std::vector<int> v;
        v.reserve(n);
        for (unsigned int i = 0; i < n; ++i)
        {
            v.emplace_back(10*i + (i % 9));
        }
        Vector3::IntVector iv = { std::move(v) };
        return std::move(iv);
    }
};

TEST_P(IntVectorFixture, IntVectorTest)
{ 
    VerifyTest(GetParam());
}

} // namespace tests::Merge::Vector3tests
