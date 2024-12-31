# Dodaj pliki wykonywalne
add_executable(
    PointsNthElementTests
    Points1/PointsTests.cpp
)

add_executable(
    RandomStringNthElementTests
    RandomString2/RandomStringTests.cpp
)

# Dodaj Boost i GTEST do kazdego execa 
target_include_directories(PointsNthElementTests PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)
target_include_directories(RandomStringNthElementTests PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)

# Polacz z GTEST_main
target_link_libraries(PointsNthElementTests GTest::gtest_main)
target_link_libraries(RandomStringNthElementTests GTest::gtest_main)

# Dolacz testy GTEST
include(GoogleTest)
gtest_discover_tests(PointsNthElementTests)
gtest_discover_tests(RandomStringNthElementTests DISCOVERY_TIMEOUT 15) # domyslnie jest 5 sekund
