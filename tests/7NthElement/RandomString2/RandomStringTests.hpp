#pragma once

#include "../NthElementTestFixture.hpp"
#include "../../../src/Structures/RandomStringImpl.hpp"

using namespace src::Structures;

namespace tests::NthElement
{

using Container = std::vector<std::string>;
using Base = BaseTestStruct<Container>;
using Parent = NthElementTestStruct<Container>;

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

class RandomStringNthElementFixture : public NthElementTestFixture<Container>
{
};

} // namespace tests::NthElement
