# Dodaj pliki wykonywalne
add_executable(
  PointsSortTests
  Points1/PointsTests.cpp
)

add_executable(
  IntVectorSortTests
  Vector3/IntVectorTests.cpp
)

# Dodaj Boost i GTEST do kazdego execa 
target_include_directories(PointsSortTests PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)
target_include_directories(IntVectorSortTests PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)

# Polacz z GTEST_main
target_link_libraries(PointsSortTests GTest::gtest_main)
target_link_libraries(IntVectorSortTests GTest::gtest_main)

# Dolacz testy GTEST (domyslnie jest 5 sekund timeout)
include(GoogleTest)
gtest_discover_tests(PointsSortTests DISCOVERY_TIMEOUT 15)
gtest_discover_tests(IntVectorSortTests DISCOVERY_TIMEOUT 15)
