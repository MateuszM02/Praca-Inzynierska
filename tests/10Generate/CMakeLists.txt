# Dodaj pliki wykonywalne
add_executable(
  FibonacciGenerateTests
  Fibonacci1/FibonacciTests.cpp
)

add_executable(
  RandomStringGenerateTests
  RandomString2/RandomStringTests.cpp
)

add_executable(
  MatrixGenerateTests
  Matrix3/MatrixTests.cpp
)

# Dodaj Boost i GTEST do kazdego execa 
target_include_directories(FibonacciGenerateTests PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)
target_include_directories(RandomStringGenerateTests PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)
target_include_directories(MatrixGenerateTests PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)

# Polacz z GTEST_main
target_link_libraries(FibonacciGenerateTests GTest::gtest_main)
target_link_libraries(RandomStringGenerateTests GTest::gtest_main)
target_link_libraries(MatrixGenerateTests GTest::gtest_main)

# Dolacz testy GTEST
include(GoogleTest)
gtest_discover_tests(FibonacciGenerateTests)
gtest_discover_tests(RandomStringGenerateTests)
gtest_discover_tests(MatrixGenerateTests)
