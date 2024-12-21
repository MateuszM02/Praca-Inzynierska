# Dodaj pliki wykonywalne
add_executable(
    PointsNthElementTests
    Points1/PointsTests.cpp
)

# Dodaj Boost i GTEST do kazdego execa 
target_include_directories(PointsNthElementTests PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)

# Polacz z GTEST_main
target_link_libraries(PointsNthElementTests GTest::gtest_main)

# Dolacz testy GTEST
include(GoogleTest)
gtest_discover_tests(PointsNthElementTests)
