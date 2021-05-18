cmake_minimum_required(VERSION 3.12)
project(PriorityQueue C)

set(CMAKE_C_STANDARD 11)
file(GLOB_RECURSE src_list "lib/*.h" "lib/*.c")
add_executable(PriorityQueue main.c ${src_list})
add_executable(tPriorityQueue test.c lib/priorityQueue.c lib/priorityQueue.h)