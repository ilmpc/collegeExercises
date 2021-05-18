cmake_minimum_required(VERSION 3.12)
project(Diff C)

set(CMAKE_C_STANDARD 11)
#enable_testing()

add_executable(Diff src/main.c src/compare.c src/compare.h)
add_executable(Test test/tests.c src/compare.c src/compare.h)
#add_test(Test Test)