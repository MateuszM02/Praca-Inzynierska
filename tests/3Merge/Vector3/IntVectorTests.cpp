#include "IntVectorTests.hpp"

namespace tests::Merge
{

IntVectorArgs::IntVectorArgs(
    const std::string& path,
    MergerData<IntVector> vectors)
: MergeTestStruct<IntVector>(
    path,
    std::move(std::make_shared<Merger<IntVector>>(std::move(vectors))))
{ }

INSTANTIATE_TEST_SUITE_P(
    IntVectorPrefix,
    IntVectorFixture,
    ::testing::Values(
        std::move(IntVectorArgs(
                    Path::Create(MergeIntVector, 1),
                    std::move(IntVectorFixture::initTestData(
                                IntVectorFixture::f10i_imod7,
                                IntVectorFixture::f10i_imod9,
                                3000,
                                3000)))),
        std::move(IntVectorArgs(
                    Path::Create(MergeIntVector, 2),
                    std::move(IntVectorFixture::initTestData(
                                IntVectorFixture::f10i_imod7,
                                IntVectorFixture::f10i_imod9,
                                4000,
                                2000)))),
        std::move(IntVectorArgs(
                    Path::Create(MergeIntVector, 3),
                    std::move(IntVectorFixture::initTestData(
                                IntVectorFixture::f10i_imod7,
                                IntVectorFixture::f10i_imod9,
                                5000,
                                1000)))),
        std::move(IntVectorArgs(
                    Path::Create(MergeIntVector, 4),
                    std::move(IntVectorFixture::initTestData(
                                IntVectorFixture::f10i_imod7,
                                IntVectorFixture::f10i_imod9,
                                5400,
                                5400)))),
        std::move(IntVectorArgs(
                    Path::Create(MergeIntVector, 5),
                    std::move(IntVectorFixture::initTestData(
                                IntVectorFixture::f10i_imod7,
                                IntVectorFixture::f10i_imod9,
                                7400,
                                3400)))),
        std::move(IntVectorArgs(
                    Path::Create(MergeIntVector, 6),
                    std::move(IntVectorFixture::initTestData(
                                IntVectorFixture::f10i_imod7,
                                IntVectorFixture::f10i_imod9,
                                9400,
                                1400))))
    ));

} // namespace tests::Merge
