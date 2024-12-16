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
    : BaseClass<std::string, std::vector<std::string>>({})
    , text_(std::move(data.text_))
    , pattern_(std::move(data.pattern_))
    , matchedSubstrings_({})
    { 
        this->expectedResult_ = this->executeSimple();
    }

private:
    void resetData() override
    {
        this->matchedSubstrings_ = {};
    }

    std::vector<std::string> executeSTL() override
    {
        std::regex regex(this->pattern_);
        auto it = std::sregex_iterator(this->text_.begin(), this->text_.end(), regex);
        
        for (auto itEnd = std::sregex_iterator(); it != itEnd; ++it)
        {
            this->matchedSubstrings_.emplace_back(it->str());
        }
        return this->matchedSubstrings_;
    }

    std::vector<std::string> executeBoost() override
    {
        boost::regex regex(this->pattern_);
        auto it = boost::sregex_iterator(this->text_.begin(), this->text_.end(), regex);
        
        for (auto itEnd = boost::sregex_iterator(); it != itEnd; ++it)
        {
            this->matchedSubstrings_.emplace_back(it->str());
        }
        return this->matchedSubstrings_;
    }

    std::vector<std::string> executeSimple() override
    {
        std::string::size_type pos = 0;

        while (pos < this->text_.size())
        {
            // Znajdz poczatek wzorca
            pos = this->text_.find(this->pattern_, pos);
            if (pos == std::string::npos)   break;

            this->matchedSubstrings_.emplace_back(
                this->text_.substr(pos, this->pattern_.length()));

            // Przesun pozycje o dlugosc wzorca, aby szukac kolejnego wystapienia
            pos += this->pattern_.length();
        }
        return this->matchedSubstrings_;
    }

public:
    std::vector<std::string> matchedSubstrings_;
    const std::string text_;
    const std::string pattern_;
};

} // namespace src::Algorithms
