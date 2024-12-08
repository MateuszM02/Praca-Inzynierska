#pragma once
#include "../Functor.hpp"

#include <random>

// Przyklad 2. Losowe slowa podanej dlugosci ----------------------------------------------------------------

namespace src::Generate::RandomString2
{
class RandomStringFunctor : public Functor<std::string>
{
public:
    RandomStringFunctor(const unsigned int l);
    std::string operator()() override;
    std::shared_ptr<Functor<std::string>> clone() const override;
private:
    unsigned int length;
    std::mt19937 randomGenerator;
    std::uniform_int_distribution<> distribution;
};
} // namespace src::Generate::RandomString2
