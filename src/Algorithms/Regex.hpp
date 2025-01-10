#pragma once

#include "Base.hpp"

#include <regex> // std::regex
#include <boost/regex.hpp> // boost::regex

namespace src::Algorithms
{

struct RegexData final
{
    explicit RegexData(const std::string& text, const std::string& pattern)
    : text_{text}
    , pattern_{pattern}
    { }

    const std::string text_;
    const std::string pattern_;
};

class RegexEvaluator final : public BaseClass<std::vector<std::string>>
{
public:
    explicit RegexEvaluator(const RegexData& data)
    : text_{std::move(data.text_)}
    , pattern_{std::move(data.pattern_)}
    { }

private:
    void resetData() const override { }

    std::vector<std::string> executeSTL() const override
    {
        std::regex regex(pattern_);
        std::vector<std::string> matchedSubstrings;

        auto it = std::sregex_iterator(text_.cbegin(), text_.cend(), regex);
        for (auto itEnd = std::sregex_iterator(); it != itEnd; ++it)
        {
            matchedSubstrings.emplace_back(it->str());
        }
        return matchedSubstrings;
    }

    std::vector<std::string> executeBoost() const override
    {
        boost::regex regex(pattern_);
        std::vector<std::string> matchedSubstrings;

        auto it = boost::sregex_iterator(text_.cbegin(), text_.cend(), regex);
        for (auto itEnd = boost::sregex_iterator(); it != itEnd; ++it)
        {
            matchedSubstrings.emplace_back(it->str());
        }
        return matchedSubstrings;
    }

    std::vector<std::string> executeSimple() const override
    {
        std::regex regex(pattern_);
        std::vector<std::string> matchedSubstrings;

        std::string::const_iterator searchStart(text_.cbegin());
        std::smatch match;

        while (std::regex_search(searchStart, text_.cend(), match, regex))
        {
            matchedSubstrings.emplace_back(match.str());
            searchStart = match.suffix().first;
        }

        return matchedSubstrings;
    }

private:
    const std::string text_;
    const std::string pattern_;
};

} // namespace src::Algorithms
