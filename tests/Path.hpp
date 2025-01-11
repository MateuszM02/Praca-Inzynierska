#pragma once

#include <string>
#include <unordered_map>

namespace tests
{

enum class TestType : unsigned char
{
    MinMaxBasicVector,
    MinMaxVectorOfVectors,
    MinMaxBasicSet,
    MinMaxVectorSet,
    AccumulateUint,
    AccumulatePoints,
    AccumulateMatrix,
    MergePoints,
    MergeIntVector,
    SortPoints,
    SortIntVector,
    // TODO: wiecej typow 5
    TransformMatrixToIntVector,
    // TODO: typy 6
    NthElementPoints,
    NthElementRandomString,
    RegexType,
    // TODO: wiecej typow 9
    RemoveEraseIfSequence,
    GenerateFibonacci,
    GenerateRandomString,
    GenerateMatrix
};

class Path final
{
public:
    Path() = delete;

    static std::string Create(const TestType testType)
    {
        static std::unordered_map<TestType, unsigned int> testIdMap;
        return Convert(testType) + std::to_string(++testIdMap[testType]) + ".txt";
    }

private:
    static std::string Convert(const TestType testType)
    {
        switch (testType)
        {
            case TestType::MinMaxBasicVector:           return "BasicVector";
            case TestType::MinMaxVectorOfVectors:       return "VectorOfVectors";
            case TestType::MinMaxBasicSet:              return "BasicSet";
            case TestType::MinMaxVectorSet:             return "VectorSet";
            case TestType::AccumulateUint:              return "UInt";
            case TestType::AccumulatePoints:            return "Points";
            case TestType::AccumulateMatrix:            return "Matrix";
            case TestType::MergePoints:                 return "Points";
            case TestType::MergeIntVector:              return "IntVector";
            case TestType::SortPoints:                  return "Points";
            case TestType::SortIntVector:               return "IntVector";
            // TODO: wiecej typow 5
            case TestType::TransformMatrixToIntVector:  return "MatrixToIntVector";
            // TODO: typy 6
            case TestType::NthElementPoints:            return "Points";
            case TestType::NthElementRandomString:      return "RandomString";
            case TestType::RegexType:                   return "Regex";
            // TODO: wiecej typow 9
            case TestType::RemoveEraseIfSequence:       return "Sequence";
            case TestType::GenerateFibonacci:           return "Fibonacci";
            case TestType::GenerateRandomString:        return "RandomString";
            case TestType::GenerateMatrix:              return "Matrix";
            default:                                    return "!!! Nieznany typ testu !!!";
        }
    }
};

} // namespace tests
