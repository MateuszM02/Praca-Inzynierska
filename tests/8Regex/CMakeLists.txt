# Dodaj pliki wykonywalne
add_executable(
  RegexTests
  RegexTests.cpp
)

# Dodaj Boost i GTEST do kazdego execa 
target_include_directories(RegexTests PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)

# Polacz z GTEST_main
target_link_libraries(RegexTests GTest::gtest_main)

# Dolacz testy GTEST
include(GoogleTest)
gtest_discover_tests(RegexTests)
