#include "SequenceTests.hpp"

#define MERSENNE_TEST_SIZE 100'000
#define DIVISORS_TEST_SIZE 150'000
#define SUM_TEST_SIZE 25'000

namespace tests::RemoveEraseIf
{

template <Removable Container>
SequenceArgs<Container>::SequenceArgs(
    const std::string& path,
    RemoverData<unsigned int, Container> elements)
: RemoveEraseIfTestStruct<unsigned int>(
    path,
    std::move(std::make_shared<Remover<unsigned int, Container>>(std::move(elements))))
{ }

INSTANTIATE_TEST_SUITE_P(
    SequencePrefix,
    SequenceIntFixture,
    ::testing::Values(
        std::move(SequenceArgs(
                    Path::Create(RemoveEraseIfSequence, 1),
                    std::move(SequenceIntFixture::initTestData(
                                SequenceIntFixture::identity,
                                SequenceIntFixture::isMersenneNumber,
                                MERSENNE_TEST_SIZE)))),
        std::move(SequenceArgs(
                    Path::Create(RemoveEraseIfSequence, 2),
                    std::move(SequenceIntFixture::initTestData(
                                SequenceIntFixture::identity,
                                SequenceIntFixture::hasAtMost4Divisors,
                                DIVISORS_TEST_SIZE)))),
        std::move(SequenceArgs(
                    Path::Create(RemoveEraseIfSequence, 3),
                    std::move(SequenceIntFixture::initTestData(
                                SequenceIntFixture::identity,
                                SequenceIntFixture::is1toNSumOdd,
                                SUM_TEST_SIZE))))
    ));

} // namespace tests::RemoveEraseIf
