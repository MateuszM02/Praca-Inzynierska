#pragma once

#include "../../../src/Structures/RandomStringImpl.hpp"
#include "../GenerateTestFixture.hpp"

using namespace src::Structures;

namespace tests::Generate
{

struct RandomStringGenerateArgs final : public GenerateTestStruct<std::string, RandomString>
{
    explicit RandomStringGenerateArgs(const unsigned int l, const unsigned int n)
    : GenerateTestStruct<std::string, RandomString>(
        TestType::GenerateRandomString,
        [n, l]()
        {
            return RandomStringImpl::createGenerator(n, l);
        })
    { }
};

class RandomStringGenerateFixture : public GenerateTestFixture<std::string, RandomString>
{
public:
    void VerifyTestCustomForRandomStringGenerator(
        const std::shared_ptr<BaseTestStruct<std::vector<std::string>>>& args)
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
            EXPECT_EQ_OS(stlResult[i].size(), boostResult[i].size(), os)
                << "Rozmiar STL rozni sie od rozmiaru Boost na indeksie " << i;
            EXPECT_EQ_OS(stlResult[i].size(), simpleResult[i].size(), os)
                << "Rozmiar STL rozni sie od rozmiaru Simple na indeksie " << i;
            EXPECT_EQ_OS(boostResult[i].size(), simpleResult[i].size(), os)
                << "Rozmiar Boost rozni sie od rozmiaru Simple na indeksie " << i;
        }
    }
};

TEST_P(RandomStringGenerateFixture, RandomStringGenerateTest) 
{
    VerifyTestCustomForRandomStringGenerator(GetParam());
}

} // namespace tests::Generate
