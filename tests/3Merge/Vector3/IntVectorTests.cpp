#include "IntVectorTests.hpp"

namespace tests::Merge
{

INSTANTIATE_TEST_SUITE_P(
    IntVectorPrefix,
    IntVectorFixture,
    ::testing::Values(
        IntVectorArgs(IntVectorFixture::f10i_imod7,
                      IntVectorFixture::f10i_imod9,
                      3000, 3000),
        IntVectorArgs(IntVectorFixture::f10i_imod7,
                      IntVectorFixture::f10i_imod9,
                      4000, 2000),
        IntVectorArgs(IntVectorFixture::f10i_imod7,
                      IntVectorFixture::f10i_imod9,
                      5000, 1000),
        IntVectorArgs(IntVectorFixture::f10i_imod7,
                      IntVectorFixture::f10i_imod9,
                      5400, 5400),
        IntVectorArgs(IntVectorFixture::f10i_imod7,
                      IntVectorFixture::f10i_imod9,
                      7400, 3400),
        IntVectorArgs(IntVectorFixture::f10i_imod7,
                      IntVectorFixture::f10i_imod9,
                      9400, 1400)
    ));

} // namespace tests::Merge
