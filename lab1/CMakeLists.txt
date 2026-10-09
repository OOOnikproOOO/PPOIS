cmake_minimum_required(VERSION 3.14)
project(PPOIS_lab1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab1_Run app/main.cpp src/Set.cpp src/TicTacToe.cpp)
target_include_directories(Lab1_Run PRIVATE include)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(Tests_Run tests/tests.cpp src/Set.cpp src/TicTacToe.cpp)
target_include_directories(Tests_Run PRIVATE include)

target_link_libraries(Tests_Run gtest_main)

include(GoogleTest)
gtest_discover_tests(Tests_Run)