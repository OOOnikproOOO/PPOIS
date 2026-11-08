cmake_minimum_required(VERSION 3.14)
project(PPOIS_lab2)

if(ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(Lab2_Run app/main.cpp ${SRC_FILES})
target_include_directories(Lab2_Run PRIVATE include)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS "tests/*.cpp")

add_executable(Tests_Run ${TEST_FILES} ${SRC_FILES})
target_include_directories(Tests_Run PRIVATE include)

target_link_libraries(Tests_Run gtest_main)

include(GoogleTest)
gtest_discover_tests(Tests_Run)
