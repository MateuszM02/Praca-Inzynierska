#include "RandomStringFunctor.hpp"

namespace src::Generate::RandomString2
{
RandomStringFunctor::RandomStringFunctor(const unsigned int l) 
: length(l)
, randomGenerator(std::random_device{}())
, distribution('a', 'z')
{ }

std::string RandomStringFunctor::operator()()
{
    std::string randomString; 
    randomString.reserve(length); 
    for (unsigned int i = 0; i < length; ++i) 
    { 
        randomString += distribution(randomGenerator); 
    } 
    return randomString;
}
} // namespace src::Generate::RandomString2
