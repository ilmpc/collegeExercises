cmake_minimum_required(VERSION 3.12)
project(Stacc)

set(CMAKE_CXX_STANDARD 17)
file(GLOB_RECURSE src_list "lib/*.h" "lib/*.cpp")
add_executable(Stacc main.cpp ${src_list})