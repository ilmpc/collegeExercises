cmake_minimum_required(VERSION 3.10)
project(HashSet C)

set(CMAKE_C_STANDARD 11)

add_library(HashSet src/set.c src/set.h)
add_executable(Debug debug.c debug2.c debug2.h)
target_link_libraries(Debug HashSet)