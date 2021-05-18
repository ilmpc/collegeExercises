cmake_minimum_required(VERSION 3.10)
project(String)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(googletest)
include_directories(googletest/googletest)

add_library(String String.cpp String.hpp)
add_executable(Debug test.cpp NullTests.cpp)
target_link_libraries(Debug gtest gtest_main)
target_link_libraries(Debug String)