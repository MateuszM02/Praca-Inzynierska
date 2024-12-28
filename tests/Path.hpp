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
    // TODO: typy 4
    SortPoints,
    SortIntVector,
    // TODO: typy 6
    NthElementPoints,
    NthElementRandomString,
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
            case MergePoints:               return "Points";
            case MergeTree:                 return "Tree";
            case MergeIntVector:            return "IntVector";
            // TODO: typy 4
            case SortPoints:                return "Points";
            case SortIntVector:             return "IntVector";
            // TODO: typy 6
            case NthElementPoints:          return "Points";
            case NthElementRandomString:    return "RandomString";
            case RegexType:                 return "Regex";
            // TODO: typy 9
            case RemoveEraseIfSequence:     return "Sequence";
            case GenerateFibonacci:         return "Fibonacci";
            case GenerateRandomString:      return "RandomString";
            case GenerateMatrix:            return "Matrix";
            default:                        return "!!! Nieznany typ testu !!!";
        }
    }
};

} // namespace tests
