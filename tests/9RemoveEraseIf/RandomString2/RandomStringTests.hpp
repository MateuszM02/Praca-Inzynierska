#pragma once

#include "../../../src/Structures/RandomStringImpl.hpp"
#include "../RemoveEraseIfTestFixture.hpp"

using namespace src::Structures;

namespace tests::RemoveEraseIf
{

using Container2 = std::vector<std::string>;
using Base2 = BaseTestStruct<Container2>;
using Parent2 = RemoveEraseIfTestStruct<Container2>;

struct RandomStringRemoveEraseIfArgs final : public Parent2
{
    explicit RandomStringRemoveEraseIfArgs(
        bool(*predicate)(const std::string&),
        const TestPair& info)
    : Parent2(TestType::RemoveEraseIfSequence,
        [predicate, info]()
        {
            return initTestData9(generateRandomString, predicate, info);
        })
    { }

    static std::string generateRandomString(const unsigned int length)
    {
        static CopyableRandomString rs(length);
        return rs();
    }
};

class RandomStringRemoveEraseIfFixture : public RemoveEraseIfTestFixture<Container2>
{
private:
    static bool isVowel(const char c)
    {
        char loweredChar = std::tolower(c);
        switch (loweredChar)
        {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
            case 'y':
                     return true;
            default: return false;
        }
    }

public:
    // predykaty
    static bool startsWithVowel(const std::string& value)
    {
        if (value.empty()) return false;
        return isVowel(value[0]);
    }

    static bool moreVowelsThanConsonants(const std::string& value)
    {
        int vowelsCount = 0;
        for (const char c : value)
        {
            if (isVowel(c))             vowelsCount++;
            else if (std::isalpha(c))   vowelsCount--;
        }
        return vowelsCount > 0;
    }

};

} // namespace tests::RemoveEraseIf
