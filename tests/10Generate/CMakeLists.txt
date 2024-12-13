set(SRC_DIR "../../src/Structures")

# Dodaj pliki wykonywalne
add_executable(
  FibonacciTests
  Fibonacci1/FibonacciTests.cpp
  ${SRC_DIR}/FibonacciFunctor.cpp
)

add_executable(
  RandomStringTests
  RandomString2/RandomStringTests.cpp
  ${SRC_DIR}/RandomStringFunctor.cpp
)

add_executable(
  MatrixTests
  Matrix3/MatrixTests.cpp
  ${SRC_DIR}/MatrixFunctor.cpp
  ${SRC_DIR}/Matrix.cpp
)

# Dodaj Boost i GTEST do kazdego execa 
target_include_directories(FibonacciTests PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)
target_include_directories(RandomStringTests PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)
target_include_directories(MatrixTests PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)

# Polacz z GTEST_main
target_link_libraries(FibonacciTests GTest::gtest_main)
target_link_libraries(RandomStringTests GTest::gtest_main)
target_link_libraries(MatrixTests GTest::gtest_main)

# Dolacz testy GTEST
include(GoogleTest)
gtest_discover_tests(FibonacciTests)
gtest_discover_tests(RandomStringTests)
gtest_discover_tests(MatrixTests)
