#pragma once

#include "../NthElementTestFixture.hpp"
#include "../../../src/Structures/RandomStringImpl.hpp"

using namespace src::Structures;

namespace tests::NthElement
{

using Base = BaseTestStruct<std::vector<std::string>>;
using Parent = NthElementTestStruct<std::vector<std::string>>;

struct RandomStringNthElementArgs final : public Parent
{
    explicit RandomStringNthElementArgs(
        const unsigned int stringLength,
        const TestPair& info)
    : Parent(TestType::NthElementRandomString,
        [stringLength, info]()
        {
            return RandomStringImpl::createFinder(stringLength, info);
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
