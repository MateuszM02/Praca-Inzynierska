#include "RegexTests.hpp"

#define SMALL_TEXT_SIZE 10'000
#define MEDIUM_TEXT_SIZE 100'000

namespace tests::Regex
{

// TODO: Naprawic niedzialajace testy

// INSTANTIATE_TEST_SUITE_P(
//     RegexPrefix,
//     RegexTestFixture,
//     ::testing::Values(
//         std::move(RegexTestStruct(
//                     Path::Create(RegexType, 1),
//                     std::move(RegexTestFixture::initTestData(
//                                 RegexTestFixture::dateTextGenerator,
//                                 RegexTestFixture::datePatternGenerator,
//                                 SMALL_TEXT_SIZE, 0)))),
//         std::move(RegexTestStruct(
//                     Path::Create(RegexType, 2),
//                     std::move(RegexTestFixture::initTestData(
//                                 RegexTestFixture::dateTextGenerator,
//                                 RegexTestFixture::datePatternGenerator,
//                                 MEDIUM_TEXT_SIZE, 0)))),
//         std::move(RegexTestStruct(
//                     Path::Create(RegexType, 3),
//                     std::move(RegexTestFixture::initTestData(
//                                 RegexTestFixture::phoneTextGenerator,
//                                 RegexTestFixture::phonePatternGenerator,
//                                 SMALL_TEXT_SIZE, 0)))),
//         std::move(RegexTestStruct(
//                     Path::Create(RegexType, 4),
//                     std::move(RegexTestFixture::initTestData(
//                                 RegexTestFixture::phoneTextGenerator,
//                                 RegexTestFixture::phonePatternGenerator,
//                                 MEDIUM_TEXT_SIZE, 0))))
//     ));

} // namespace tests::Regex
