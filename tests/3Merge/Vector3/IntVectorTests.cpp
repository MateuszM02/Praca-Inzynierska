#include "IntVectorTests.hpp"

namespace tests::Merge
{

INSTANTIATE_TEST_SUITE_P(
    MergePrefix,
    IntVectorMergeFixture,
    ::testing::Values(
        std::make_shared<IntVectorMergeArgs>(
            IntVectorMergeFixture::f10i_imod7,
            IntVectorMergeFixture::f10i_imod9,
            3000, 3000),
        std::make_shared<IntVectorMergeArgs>(
            IntVectorMergeFixture::f10i_imod7,
            IntVectorMergeFixture::f10i_imod9,
            4000, 2000),
        std::make_shared<IntVectorMergeArgs>(
            IntVectorMergeFixture::f10i_imod7,
            IntVectorMergeFixture::f10i_imod9,
            5000, 1000),
        std::make_shared<IntVectorMergeArgs>(
            IntVectorMergeFixture::f10i_imod7,
            IntVectorMergeFixture::f10i_imod9,
            5400, 5400),
        std::make_shared<IntVectorMergeArgs>(
            IntVectorMergeFixture::f10i_imod7,
            IntVectorMergeFixture::f10i_imod9,
            7400, 3400),
        std::make_shared<IntVectorMergeArgs>(
            IntVectorMergeFixture::f10i_imod7,
            IntVectorMergeFixture::f10i_imod9,
            9400, 1400)
    ));

} // namespace tests::Merge
