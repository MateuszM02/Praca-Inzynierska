#pragma once

#include <string>

namespace tests
{

enum TestType
{
    // TODO: typy 1,2
    MergePoints,
    MergeTree,
    MergeIntVector,
    // TODO: typy 4, 5, 6, 7
    RegexType,
    // TODO: typy 9
    RemoveEraseIfSequence,
    GenerateFibonacci,
    GenerateRandomString,
    GenerateMatrix
};

class Path final
{
public:
    Path() = delete;

    static std::string Create(const TestType type, const unsigned int id)
    {
        return Convert(type) + std::to_string(id) + ".txt";
    }

private:
    static std::string Convert(const TestType type)
    {
        switch (type)
        {
            // TODO: typy 1, 2
            case TestType::MergePoints:             return "Points";
            case TestType::MergeTree:               return "Tree";
            case TestType::MergeIntVector:          return "IntVector";
            // TODO: typy 4, 5, 6, 7
            case TestType::RegexType:               return "Regex";
            // TODO: typy 9
            case TestType::RemoveEraseIfSequence:   return "Sequence";
            case TestType::GenerateFibonacci:       return "Fibonacci";
            case TestType::GenerateRandomString:    return "RandomString";
            case TestType::GenerateMatrix:          return "Matrix";
            default:                                return "!!! Nieznany typ testu !!!";
        }
    }
};

} // namespace tests
