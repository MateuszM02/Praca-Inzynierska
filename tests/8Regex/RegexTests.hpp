#pragma once

#include "../BaseTestFixture.hpp"
#include "../../src/Algorithms/Regex.hpp"
#include "../Path.hpp"
#include "RegexGenerators.hpp"

using namespace src::Algorithms;

namespace tests::Regex
{

enum ERegexTestType
{
    phone,
    date
};

struct RegexTestStruct final : public BaseTestStruct<RegexEvaluator>
{
public:
    RegexTestStruct(const unsigned int textLength, const ERegexTestType testType)
    : BaseTestStruct<RegexEvaluator>(createPath(RegexType), createEvaluatorPtr(textLength, testType))
    { }

private:
    static std::shared_ptr<RegexEvaluator> createEvaluatorPtr(
        const unsigned int textLength, const ERegexTestType testType)
    {
        std::string(*textGenerator)(const unsigned int);
        std::string(*patternGenerator)();

        switch (testType)
        {
            case date:
                textGenerator = RegexGenerators::dateTextGenerator;
                patternGenerator = RegexGenerators::datePatternGenerator;
                break;
            case phone:
                textGenerator = RegexGenerators::phoneTextGenerator;
                patternGenerator = RegexGenerators::phonePatternGenerator;
                break;
            default:
                throw new std::invalid_argument("Zla wartosc enuma!");
        }

        // generuj tekst i wzorzec
        const std::string text = textGenerator(textLength);
        const std::string pattern = patternGenerator();
        const RegexData data(std::move(text), std::move(pattern));

        return std::make_shared<RegexEvaluator>(std::move(data));
    }
};

class RegexTestFixture : public BaseTestFixture<RegexEvaluator>
{
};

TEST_P(RegexTestFixture, RegexTest)
{
    VerifyTest(GetParam());
}

} // namespace tests::Regex
