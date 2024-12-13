#pragma once
#include "../Algorithms/Functor.hpp"

#include <random>

using namespace src::Algorithms;

namespace src::Structures
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
} // namespace src::Structures
