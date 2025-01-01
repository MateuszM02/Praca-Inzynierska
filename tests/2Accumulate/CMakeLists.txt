# Dodaj pliki wykonywalne
add_executable(
  UintAccumulateTests
  UInt1/UIntTests.cpp
)

add_executable(
  PointsAccumulateTests
  Points2/PointsTests.cpp
)

add_executable(
  MatrixAccumulateTests
  Matrix3/MatrixTests.cpp
)

# Dodaj Boost i GTEST do kazdego execa 
target_include_directories(UintAccumulateTests PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)
target_include_directories(PointsAccumulateTests PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)
target_include_directories(MatrixAccumulateTests PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)

# Polacz z GTEST_main
target_link_libraries(UintAccumulateTests GTest::gtest_main)
target_link_libraries(PointsAccumulateTests GTest::gtest_main)
target_link_libraries(MatrixAccumulateTests GTest::gtest_main)

# Dolacz testy GTEST (domyslnie jest 5 sekund timeout)
include(GoogleTest)
gtest_discover_tests(UintAccumulateTests)
gtest_discover_tests(PointsAccumulateTests DISCOVERY_TIMEOUT 15)
gtest_discover_tests(MatrixAccumulateTests DISCOVERY_TIMEOUT 15)
