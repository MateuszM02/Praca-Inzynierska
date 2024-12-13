#pragma once
#include "../MergeTestFixture.hpp"
#include "../../Path.hpp"
#include "../../../src/Structures/IntVector.hpp"

#include <functional>
#include <random>

using namespace src::Structures;

namespace tests::Merge
{

struct IntVectorArgs : public MergeTestStruct<IntVector>
{
    IntVectorArgs(
        const std::string& path,
        VectorStruct<IntVector> vectors);
};

class IntVectorFixture : public MergeTestFixture<IntVector>
{
public:
    static IntVector f10i_imod7(const int n)
    {
        std::vector<int> v;
        v.reserve(n);
        for (unsigned int i = 0; i < n; ++i)
        {
            v.emplace_back(10*i + ((i+1) % 7));
        }
        IntVector iv = { std::move(v) };
        return std::move(iv);
    }

    static IntVector f10i_imod9(const int n)
    {
        std::vector<int> v;
        v.reserve(n);
        for (unsigned int i = 0; i < n; ++i)
        {
            v.emplace_back(10*i + (i % 9));
        }
        IntVector iv = { std::move(v) };
        return std::move(iv);
    }
};

TEST_P(IntVectorFixture, IntVectorTest)
{ 
    VerifyTest(GetParam());
}

} // namespace tests::Merge
