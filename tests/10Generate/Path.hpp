#pragma once
#include <string>
#include <unordered_map>

namespace tests::Generate
{

enum GenerateType
{
    Fibonacci,
    RandomString,
    Matrix
};

class Path
{
public:
    Path() = delete;

    static std::string Create(const GenerateType type, const unsigned int id)
    {
        return Convert(type) + std::to_string(id) + ".txt";
    }

private:
    static std::string Convert(const GenerateType type)
    { 
        static const std::unordered_map<GenerateType, std::string> typeMap = {
            { Fibonacci, "Fibonacci" },
            { RandomString, "RandomString" },
            { Matrix, "Matrix" }
        };
        return typeMap.at(type);
    }
};

} // namespace tests::Generate
