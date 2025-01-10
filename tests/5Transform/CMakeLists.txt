# Ustal nazwy plikow wykonywalnych
set(TEST_EXECUTABLES
  TransformMatrixToIntVector
)

# Dodaj pliki wykonywalne
add_executable(
  TransformMatrixToIntVector
  MatrixToIntVector1/TransformTests.cpp
)

# Dodaj Boost i GTEST do kazdego execa, polacz z GTEST_main oraz dodaj testy
include(GoogleTest)
foreach(TEST_EXEC ${TEST_EXECUTABLES})
  target_include_directories(${TEST_EXEC} PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)
  target_link_libraries(${TEST_EXEC} GTest::gtest_main)
  gtest_discover_tests(${TEST_EXEC})
endforeach()
