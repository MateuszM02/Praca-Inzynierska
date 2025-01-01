# Dodaj pliki wykonywalne
add_executable(
  UintAccumulateTests
  UInt/UIntTests.cpp
)

add_executable(
  PointsAccumulateTests
  Points/PointsTests.cpp
)

# Dodaj Boost i GTEST do kazdego execa 
target_include_directories(UintAccumulateTests PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)
target_include_directories(PointsAccumulateTests PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)

# Polacz z GTEST_main
target_link_libraries(UintAccumulateTests GTest::gtest_main)
target_link_libraries(PointsAccumulateTests GTest::gtest_main)

# Dolacz testy GTEST
include(GoogleTest)
gtest_discover_tests(UintAccumulateTests)
gtest_discover_tests(PointsAccumulateTests)
