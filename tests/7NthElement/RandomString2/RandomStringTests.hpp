#pragma once

#include "../NthElementTestFixture.hpp"
#include "../../../src/Structures/RandomStringImpl.hpp"

using namespace src::Structures;

namespace tests::NthElement
{

struct RandomStringNthElementArgs : public NthElementTestStruct<std::string>
{
    RandomStringNthElementArgs(
        const unsigned int n,
        const unsigned int vectorSize,
        const unsigned int stringLength)
    : NthElementTestStruct<std::string>(
        NthElementRandomString,
        RandomStringImpl::createFinder(n, vectorSize, stringLength))
    { }
};

class RandomStringNthElementFixture : public NthElementTestFixture<std::string>
{
};

TEST_P(RandomStringNthElementFixture, RandomStringNthElementTest)
{
    VerifyTestCustomFor7(GetParam());
}

} // namespace tests::NthElement
