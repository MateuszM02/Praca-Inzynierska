#pragma once

#include "Base.hpp"

#include <regex> // std::regex
#include <boost/regex.hpp> // boost::regex

namespace src::Algorithms
{

struct RegexData final
{
    RegexData(
        const std::string& text,
        const std::string& pattern)
    : text_{text}
    , pattern_{pattern}
    { }

    const std::string text_;
    const std::string pattern_;
};

class RegexEvaluator final : public BaseClass<std::string, std::vector<std::string>>
{
public:
    RegexEvaluator(RegexData data)
    : text_(std::move(data.text_))
    , pattern_(std::move(data.pattern_))
    , matchedSubstrings_({})
    { }

private:
    void resetData() override
    {
        matchedSubstrings_ = {};
    }

    std::vector<std::string> executeSTL() override
    {
        std::regex regex(pattern_);
        auto it = std::sregex_iterator(text_.cbegin(), text_.cend(), regex);
        
        for (auto itEnd = std::sregex_iterator(); it != itEnd; ++it)
        {
            matchedSubstrings_.emplace_back(it->str());
        }
        return matchedSubstrings_;
    }

    std::vector<std::string> executeBoost() override
    {
        boost::regex regex(pattern_);
        auto it = boost::sregex_iterator(text_.cbegin(), text_.cend(), regex);
        
        for (auto itEnd = boost::sregex_iterator(); it != itEnd; ++it)
        {
            matchedSubstrings_.emplace_back(it->str());
        }
        return matchedSubstrings_;
    }

    std::vector<std::string> executeSimple() override
    {
        std::regex regex(pattern_);
        std::string::const_iterator searchStart(text_.cbegin());
        std::smatch match;

        while (std::regex_search(searchStart, text_.cend(), match, regex))
        {
            matchedSubstrings_.emplace_back(match.str());
            searchStart = match.suffix().first;
        }

        return matchedSubstrings_;
    }

public:
    std::vector<std::string> matchedSubstrings_;
    const std::string text_;
    const std::string pattern_;
};

} // namespace src::Algorithms
