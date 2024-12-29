# Dodaj pliki wykonywalne
add_executable(
  UintAccumulateTests
  UInt/UIntTests.cpp
)

# Dodaj Boost i GTEST do kazdego execa 
target_include_directories(UintAccumulateTests PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)

# Polacz z GTEST_main
target_link_libraries(UintAccumulateTests GTest::gtest_main)

# Dolacz testy GTEST
include(GoogleTest)
gtest_discover_tests(UintAccumulateTests)
