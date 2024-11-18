#include "EvenFunctor.hpp"

namespace src::Generate::Even1
{
EvenFunctor::EvenFunctor() : x{0} { }

unsigned int 
EvenFunctor::operator()()
{
    x += 2;
    return x;
}
} // namespace src::Generate::Even1
