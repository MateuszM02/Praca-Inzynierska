set(SRC_DIR "../../src/Structures")

# Dodaj pliki wykonywalne
add_executable(
  PointsMergeTests
  Points1/PointsTests.cpp
)

add_executable(
  IntVectorMergeTests
  Vector3/IntVectorTests.cpp
)

# Dodaj Boost i GTEST do kazdego execa 
target_include_directories(PointsMergeTests PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)
target_include_directories(IntVectorMergeTests PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)

# Polacz z GTEST_main
target_link_libraries(PointsMergeTests GTest::gtest_main)
target_link_libraries(IntVectorMergeTests GTest::gtest_main)

# Dolacz testy GTEST
include(GoogleTest)
gtest_discover_tests(PointsMergeTests)
gtest_discover_tests(IntVectorMergeTests DISCOVERY_TIMEOUT 30) # domyslnie jest 5 sekund
