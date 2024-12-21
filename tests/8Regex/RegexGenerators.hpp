#pragma once

#include <chrono>
#include <random>

namespace tests::Regex
{

class RegexGenerators final
{
public:
    RegexGenerators() = delete;

    // generatory wzorcow
    static std::string datePatternGenerator()
    {
        // data w formacie DD-MM-R* (uproszczona walidacja, dowolny rok o ile jest dodatni)
        return R"((0[1-9]|[12][0-9]|3[01])-([1-9]|1[0-2])-\d+)";
    }

    static std::string phonePatternGenerator()
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
};

} // namespace tests::Regex
