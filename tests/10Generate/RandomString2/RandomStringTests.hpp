#include "../TestFixture.hpp"
#include "../../../src/10Generate/RandomString2/RandomStringFunctor.hpp"

namespace tests::Generate::RandomString2Tests
{

struct RandomStringArgs : public GenerateTestStruct<std::string>
{
    RandomStringArgs(unsigned int length, unsigned int n, std::vector<std::string> v);
    
    RandomString2::RandomStringFunctor functor;
};

class RandomStringFixture : public GenerateTestFixture<std::string> 
{ 
};

} // namespace tests::Generate::RandomString2Tests
