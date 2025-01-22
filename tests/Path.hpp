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
    TransformMatrixToIntVector,
    TransformVectorToMap,
    UniquePoints,
    UniqueIntVector,
    NthElementPoints,
    NthElementRandomString,
    RegexType,
    // TODO: wiecej typow 9
    RemoveEraseIfSequence,
    GenerateFibonacci,
    GenerateRandomString,
    GenerateMatrix
};

std::ostream& operator<<(std::ostream& os, const TestType& testType)
{
    switch (testType)
    {
        case TestType::MinMaxBasicVector:           return os << "BasicVector";
        case TestType::MinMaxVectorOfVectors:       return os << "VectorOfVectors";
        case TestType::MinMaxBasicSet:              return os << "BasicSet";
        case TestType::MinMaxVectorSet:             return os << "VectorSet";
        case TestType::AccumulateUint:              return os << "UInt";
        case TestType::AccumulatePoints:            return os << "Points";
        case TestType::AccumulateMatrix:            return os << "Matrix";
        case TestType::MergePoints:                 return os << "Points";
        case TestType::MergeIntVector:              return os << "IntVector";
        case TestType::SortPoints:                  return os << "Points";
        case TestType::SortIntVector:               return os << "IntVector";
        case TestType::TransformMatrixToIntVector:  return os << "MatrixToIntVector";
        case TestType::TransformVectorToMap:        return os << "VectorToMap";
        case TestType::UniquePoints:                return os << "Points";
        case TestType::UniqueIntVector:             return os << "IntVector";
        case TestType::NthElementPoints:            return os << "Points";
        case TestType::NthElementRandomString:      return os << "RandomString";
        case TestType::RegexType:                   return os << "Regex";
        // TODO: wiecej typow 9
        case TestType::RemoveEraseIfSequence:       return os << "Sequence";
        case TestType::GenerateFibonacci:           return os << "Fibonacci";
        case TestType::GenerateRandomString:        return os << "RandomString";
        case TestType::GenerateMatrix:              return os << "Matrix";
        default:                                    return os << "!!! Nieznany typ testu !!!";
    }
}

class Path final
{
public:
    Path() = delete;

    static std::string Create(const TestType& testType)
    {
        static std::unordered_map<TestType, unsigned int> testIdMap;
        std::ostringstream os;
        os << testType << ++testIdMap[testType] << ".txt";
        return os.str();
    }
};

} // namespace tests
