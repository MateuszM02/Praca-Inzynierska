#include "EvenFunctor.hpp"

namespace src::RepeatFun::Even1
{
EvenFunctor::EvenFunctor() : x{0} { }

unsigned int 
EvenFunctor::operator()()
{
    x += 2;
    return x;
}
} // namespace src::RepeatFun::Even1