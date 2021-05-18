cmake_minimum_required(VERSION 3.12)
project(Biologist)

set(CMAKE_CXX_STANDARD 17)

set(source src/Rna.cpp src/Rna.h src/Dna.cpp src/Dna.h)
add_library(mylib ${source})
add_executable(Biologist main.cpp)
target_link_libraries(Biologist mylib)

add_subdirectory(exlib/gtest/)
include_directories(exlib/gtest/googletest)

add_executable(t_Biologist tests/tests.cpp)
target_link_libraries(t_Biologist gtest gtest_main)
target_link_libraries(t_Biologist mylib)
