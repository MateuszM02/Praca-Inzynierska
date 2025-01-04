#pragma once

#include "../BaseTestFixture.hpp"
#include "../../src/Algorithms/Regex.hpp"
#include "RegexGenerators.hpp"

using namespace src::Algorithms;

namespace tests::Regex
{

enum class ERegexTestType : unsigned char
{
    phone,
    date
};

struct RegexTestStruct final : public BaseTestStruct<std::vector<std::string>>
{
public:
    explicit RegexTestStruct(const unsigned int textLength, const ERegexTestType testType)
    : BaseTestStruct<std::vector<std::string>>(TestType::RegexType, createEvaluatorPtr(textLength, testType))
    { }

private:
    static std::shared_ptr<RegexEvaluator> createEvaluatorPtr(
        const unsigned int textLength, const ERegexTestType testType)
    {
        std::string(*textGenerator)(const unsigned int);
        std::string(*patternGenerator)();

        switch (testType)
        {
            case ERegexTestType::date:
                textGenerator = RegexGenerators::dateTextGenerator;
                patternGenerator = RegexGenerators::datePatternGenerator;
                break;
            case ERegexTestType::phone:
                textGenerator = RegexGenerators::phoneTextGenerator;
                patternGenerator = RegexGenerators::phonePatternGenerator;
                break;
            default:
                throw new std::invalid_argument("Zla wartosc enuma!");
        }

        // generuj tekst i wzorzec
        const std::string& text = textGenerator(textLength);
        const std::string& pattern = patternGenerator();
        const RegexData data(text, pattern);

        return std::make_shared<RegexEvaluator>(data);
    }
};

class RegexTestFixture : public BaseTestFixture<std::vector<std::string>>
{
};

TEST_P(RegexTestFixture, RegexTest)
{
    VerifyTest(GetParam());
}

} // namespace tests::Regex
