# Dodaj pliki wykonywalne
add_executable(
  BasicVectorMinMaxTests
  BasicVector1/UIntTests.cpp
)

add_executable(
  VectorOfVectorsMinMaxTests
  VectorOfVectors2/IntVectorTests.cpp
)

add_executable(
  BasicSetMinMaxTests
  BasicSet3/UIntTests.cpp
)

add_executable(
  VectorSetMinMaxTests
  VectorSet4/IntVectorTests.cpp
)

# Dodaj Boost i GTEST do kazdego execa 
target_include_directories(BasicVectorMinMaxTests PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)
target_include_directories(VectorOfVectorsMinMaxTests PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)
target_include_directories(BasicSetMinMaxTests PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)
target_include_directories(VectorSetMinMaxTests PRIVATE ${Boost_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)

# Polacz z GTEST_main
target_link_libraries(BasicVectorMinMaxTests GTest::gtest_main)
target_link_libraries(VectorOfVectorsMinMaxTests GTest::gtest_main)
target_link_libraries(BasicSetMinMaxTests GTest::gtest_main)
target_link_libraries(VectorSetMinMaxTests GTest::gtest_main)

# Dolacz testy GTEST
include(GoogleTest)
gtest_discover_tests(BasicVectorMinMaxTests)
gtest_discover_tests(VectorOfVectorsMinMaxTests)
gtest_discover_tests(BasicSetMinMaxTests)
gtest_discover_tests(VectorSetMinMaxTests)
