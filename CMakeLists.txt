cmake_minimum_required(VERSION 3.14)
project(Praca-Inzynierska)

# GoogleTest wymaga co najmniej C++14 ale potrzeba C++20 do konceptow
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# Na Windowsie: Zapobiegaj nadpisywaniu ustawien kompilatora/linkera projektu nadrzednego.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Wlacz testowanie za pomoca komend CMake
enable_testing()

set(BOOST_ROOT "C:/boost_1_82_0") 
include_directories(${BOOST_ROOT})

add_executable(
  FibonacciTests
  tests/10Generate/Fibonacci1/FibonacciTests.cpp
  src/10Generate/Fibonacci1/FibonacciFunctor.cpp
)

add_executable(
  RandomStringTests
  tests/10Generate/RandomString2/RandomStringTests.cpp
  src/10Generate/RandomString2/RandomStringFunctor.cpp
)

# Dodaj Boost do kazdego execa 
target_include_directories(FibonacciTests PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(RandomStringTests PRIVATE ${Boost_INCLUDE_DIRS})

target_link_libraries(
  FibonacciTests
  GTest::gtest_main
)

target_link_libraries(
  RandomStringTests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(FibonacciTests)
gtest_discover_tests(RandomStringTests)

# komendy do wywolywania w glownym folderze (nie wewnatrz build)

# zaktualizuj konfiguracje po zmianie tego pliku
# cmake -S . -B build

# kompilacja testow
# cmake --build build

# odpalenie testow
# ctest --test-dir build