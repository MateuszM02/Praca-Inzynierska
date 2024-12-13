set(SRC_DIR "../../src/Structures")

# Dodaj pliki wykonywalne
add_executable(
  PointsTests
  Points1/PointsTests.cpp
  ${SRC_DIR}/Points.cpp
)

add_executable(
  TreeTests
  Trees2/TreeTests.cpp
  ${SRC_DIR}/Tree.cpp
)

add_executable(
  IntVectorTests
  Vector3/IntVectorTests.cpp
  ${SRC_DIR}/IntVector.cpp
)

# Dodaj Boost i GTEST do kazdego execa 
target_include_directories(PointsTests PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)
target_include_directories(TreeTests PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)
target_include_directories(IntVectorTests PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)

# Polacz z GTEST_main
target_link_libraries(PointsTests GTest::gtest_main)
target_link_libraries(TreeTests GTest::gtest_main)
target_link_libraries(IntVectorTests GTest::gtest_main)

# Dolacz testy GTEST
include(GoogleTest)
gtest_discover_tests(PointsTests)
gtest_discover_tests(TreeTests)
gtest_discover_tests(IntVectorTests DISCOVERY_TIMEOUT 30) # domyslnie jest 5 sekund
