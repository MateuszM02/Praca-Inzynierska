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

add_subdirectory(tests)

# komendy do wywolywania w glownym folderze (nie wewnatrz build)

# zaktualizuj konfiguracje po zmianie tego pliku
# cmake -S . -B build

# kompilacja testow
# cmake --build build

# odpalenie testow
# ctest --test-dir build