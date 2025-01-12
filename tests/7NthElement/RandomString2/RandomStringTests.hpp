#pragma once

#include "../NthElementTestFixture.hpp"
#include "../../../src/Structures/RandomStringImpl.hpp"

using namespace src::Structures;

namespace tests::NthElement
{

struct RandomStringNthElementArgs final : public NthElementTestStruct<std::vector<std::string>>
{
    explicit RandomStringNthElementArgs(
        const unsigned int n,
        const unsigned int vectorSize,
        const unsigned int stringLength)
    : NthElementTestStruct<std::vector<std::string>>(
        TestType::NthElementRandomString,
        [n, vectorSize, stringLength]()
        {
            return RandomStringImpl::createFinder(n, vectorSize, stringLength);
        })
    { }
};

class RandomStringNthElementFixture : public NthElementTestFixture<std::vector<std::string>>
{
};

TEST_P(RandomStringNthElementFixture, RandomStringNthElementTest)
{
    VerifyTestCustomFor7(GetParam());
}

} // namespace tests::NthElement
