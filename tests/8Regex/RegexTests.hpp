#pragma once

#include "../BaseTestFixture.hpp"
#include "../../src/Algorithms/Regex.hpp"
#include "../Path.hpp"

using namespace src::Algorithms;

namespace tests::Regex
{

struct RegexTestStruct final : public BaseTestStruct<RegexEvaluator>
{
public:
    RegexTestStruct(
        const std::string& path,
        std::shared_ptr<RegexEvaluator> f)
    : BaseTestStruct<RegexEvaluator>(path, std::move(f))
    { }
};

class RegexTestFixture : public BaseTestFixture<RegexEvaluator>
{
public:
    // generatory wzorcow
    static std::string datePatternGenerator(const unsigned int patternLength)
    {
        // data w formacie DD-MM-R* (uproszczona walidacja, dowolny rok o ile jest dodatni)
        return R"((0[1-9]|[12][0-9]|3[01])-([1-9]|1[0-2])-\d+)";
    }

    static std::string phonePatternGenerator(const unsigned int patternLength)
    {
        // wzorzec numeru telefonu w formacie "123 456 789"
        return R"(\d{3} \d{3} \d{3})";
    }

    // generatory tekstow spelniajacych wzorce
    static std::string randomDate()
    {
        int day = std::rand() % 31 + 1;
        int month = std::rand() % 12 + 1;
        int year = std::rand() % 100 + 2000;
        
        char buffer[11];
        snprintf(buffer, sizeof(buffer), "%02d-%02d-%d", day, month, year);
        return std::string(buffer);
    }

    static std::string randomPhoneNumber()
    {
        int part1 = rand() % 1000;
        int part2 = rand() % 1000;
        int part3 = rand() % 1000;
        
        char buffer[12];
        snprintf(buffer, sizeof(buffer), "%03d %03d %03d", part1, part2, part3);
        return std::string(buffer);
    }

    // generatory tekstow ze zwiekszonym ppb wystepowania wzorcow
    static std::string dateTextGenerator(const unsigned int textLength)
    {
        std::srand(std::time(0));
        std::string text;
        while (text.size() < textLength)
        {
            if (std::rand() % 1000 == 0)
            {
                text += randomDate() + " ";
            }
            else
            {
                char randomChar = 'a' + std::rand() % 26;
                text += randomChar;
            }
        }
        return text.substr(0, textLength);
    }

    static std::string phoneTextGenerator(const unsigned int textLength)
    {
        std::srand(std::time(0));
        std::string text;
        
        while (text.size() < textLength)
        {
            if (std::rand() % 500 == 0)
            {
                text += randomPhoneNumber() + " ";
            }
            else
            {
                char randomChar = 'a' + rand() % 26;
                text += randomChar;
            }
        }
        return text.substr(0, textLength);
    }

    // generuj tekst i wzorzec
    static std::shared_ptr<RegexEvaluator> initTestData(
        std::string(*textGenerator)(const unsigned int),
        std::string(*patternGenerator)(const unsigned int),
        const unsigned int textLength,
        const unsigned int patternLength)
    {
        const std::string text = textGenerator(textLength);
        const std::string pattern = patternGenerator(patternLength);
        const RegexData data(std::move(text), std::move(pattern));

        return std::make_shared<RegexEvaluator>(std::move(data));
    }
};

TEST_P(RegexTestFixture, RegexTest)
{
    VerifyTest(GetParam());
}

} // namespace tests::Regex
