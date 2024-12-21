# Dodaj pliki wykonywalne
add_executable(
  SequenceRemoveEraseIfTests
  Sequence1/SequenceTests.cpp
)

# Dodaj Boost i GTEST do kazdego execa 
target_include_directories(SequenceRemoveEraseIfTests PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)

# Polacz z GTEST_main
target_link_libraries(SequenceRemoveEraseIfTests GTest::gtest_main)

# Dolacz testy GTEST
include(GoogleTest)
gtest_discover_tests(SequenceRemoveEraseIfTests)
