cmake_minimum_required(VERSION 3.14)
project(Praca-Inzynierska)

# GoogleTest wymaga co najmniej C++14 ale potrzeba C++20 do konceptow
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# URL Commit hasha to https://github.com/google/googletest/pull/4662/commits
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/7927f8e93d2cc7788229ab446179fdfda15e75e4.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

# Na Windowsie: Zapobiegaj nadpisywaniu ustawien kompilatora/linkera projektu nadrzednego.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Wlacz testowanie za pomoca komend CMake
enable_testing()

# Sciezka do Boosta musi byc pod wartoscia zmiennej srodowiskowej BOOST_PATH
if(DEFINED ENV{BOOST_PATH})
  include_directories($ENV{BOOST_PATH})
else()
  message(FATAL_ERROR "BOOST_PATH environment variable is not set")
endif()

add_subdirectory(tests)

# komendy do wywolywania w glownym folderze (nie wewnatrz build)

# zaktualizuj konfiguracje po zmianie tego pliku
# cmake -S . -B build

# kompilacja testow
# cmake --build build

# odpalenie testow
# ctest --test-dir build
