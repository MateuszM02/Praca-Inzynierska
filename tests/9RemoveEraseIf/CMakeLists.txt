# Dodaj pliki wykonywalne
add_executable(
  SequenceTests
  Sequence1/SequenceTests.cpp
)

# Dodaj Boost i GTEST do kazdego execa 
target_include_directories(SequenceTests PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)

# Polacz z GTEST_main
target_link_libraries(SequenceTests GTest::gtest_main)

# Dolacz testy GTEST
include(GoogleTest)
gtest_discover_tests(SequenceTests)
