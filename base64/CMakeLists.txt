cmake_minimum_required(VERSION 3.12)
project(base64)

set(CMAKE_C_STANDARD 11)
set(lib_source lib/de_base64.c lib/de_base64.h)
add_library(mylib ${lib_source})
add_executable(base64 main.c)
target_link_libraries(base64 mylib)

add_library(b64_lib exlib/b64/b64.c exlib/b64/b64.h)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(exlib/gtest/)
include_directories(exlib/gtest/googletest)

add_executable(t_base64 tests/tests.cpp)
target_link_libraries(t_base64 gtest gtest_main)
target_link_libraries(t_base64 mylib)
target_link_libraries(t_base64 b64_lib)