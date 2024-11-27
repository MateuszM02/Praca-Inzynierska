#include "VectorTests.hpp"

namespace tests::Merge::Vector3tests
{
void VectorTest::createTest(
    const std::vector<std::vector<int>>& v1,
    const std::vector<std::vector<int>>& v2,
    const src::MethodType& methodType)
{
    auto merger = Vector3::IntVector();
    runTest(merger, v1, v2, methodType);
}
} // namespace tests::Merge::Vector3tests
