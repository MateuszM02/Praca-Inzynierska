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

std::shared_ptr<Functor<std::string>> 
RandomStringFunctor::clone() const
{
    return std::make_shared<RandomStringFunctor>(*this);
}

} // namespace src::Generate::RandomString2
