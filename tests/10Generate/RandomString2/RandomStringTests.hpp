#pragma once

#include "../../../src/Structures/RandomStringImpl.hpp"
#include "../GenerateTestFixture.hpp"

using namespace src::Structures;

namespace tests::Generate
{

struct RandomStringGenerateArgs : public GenerateTestStruct<std::string, RandomString>
{
    RandomStringGenerateArgs(const unsigned int l, const unsigned int n)
    : GenerateTestStruct<std::string, RandomString>(
        GenerateRandomString,
        std::move(RandomStringImpl::createGenerator(n, l)))
    { }
};

class RandomStringGenerateFixture : public GenerateTestFixture<std::string, RandomString>
{
public:
    void VerifyTestCustomForRandomStringGenerator(const BaseTestStruct<
        std::vector<std::string>,
        Generator<std::string, RandomString>>& args)
    {
        using namespace std::placeholders;
        auto checker = std::bind(&RandomStringGenerateFixture::verifyRandomStringGenerator, this, _1, _2, _3, _4);
        this->VerifyTest(args, checker);
    }

private:
    void verifyRandomStringGenerator(
        const std::vector<std::string>& stlResult,
        const std::vector<std::string>& boostResult,
        const std::vector<std::string>& simpleResult,
        std::ostringstream& os)
    {
        // Petla for do porownywania wynikow, jesli rozmiary sa rowne
        for (unsigned int i = 0; i < simpleResult.size(); ++i)
        {
            EXPECT_EQ(stlResult[i].size(), boostResult[i].size()) <<
                "Rozmiar STL rozni sie od rozmiaru Boost na indeksie " << i; 
            EXPECT_EQ(stlResult[i].size(), simpleResult[i].size()) <<
                "Rozmiar STL rozni sie od rozmiaru Simple na indeksie " << i; 
            EXPECT_EQ(boostResult[i].size(), simpleResult[i].size()) <<
                "Rozmiar Boost rozni sie od rozmiaru Simple na indeksie " << i; 
        }
    }
};

TEST_P(RandomStringGenerateFixture, RandomStringGenerateTest) 
{
    VerifyTestCustomForRandomStringGenerator(GetParam());
}

} // namespace tests::Generate
