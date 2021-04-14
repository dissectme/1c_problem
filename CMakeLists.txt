cmake_minimum_required(VERSION 3.0)
project(1c_problem)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(
    -Wfatal-errors
    -Wall -Wextra
    --pedantic
    )

set(INCLUDE_DIR ${1c_problem_SOURCE_DIR}/include)
set(SOURCE_DIR ${1c_problem_SOURCE_DIR}/src)
set(LODEPNG_DIR ${1c_problem_SOURCE_DIR}/lodepng)
set(TEST_DIR ${1c_problem_SOURCE_DIR}/tests)

include_directories(${INCLUDE_DIR} ${LODEPNG_DIR})

add_executable(
    a.out
    ${SOURCE_DIR}/main.cpp
    ${LODEPNG_DIR}/lodepng.cpp
    )

##############################################################
##############################################################

Include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)

add_executable(
    test
    tests/test.cpp
    )

target_link_libraries(test Catch2::Catch2)
