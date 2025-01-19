# Ustal nazwy plikow wykonywalnych
set(TEST_EXECUTABLES
  UintAccumulateTests
  PointsAccumulateTests
  MatrixAccumulateTests
)

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

# Dodaj Boost i GTEST do kazdego execa, polacz z GTEST_main oraz dodaj testy
include(GoogleTest)
foreach(TEST_EXEC ${TEST_EXECUTABLES})
  target_include_directories(${TEST_EXEC} PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)
  target_link_libraries(${TEST_EXEC} GTest::gtest_main)
  gtest_discover_tests(${TEST_EXEC})
endforeach()
