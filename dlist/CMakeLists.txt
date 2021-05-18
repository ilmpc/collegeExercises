cmake_minimum_required(VERSION 3.12)
project(DList C)

set(CMAKE_C_STANDARD 11)

add_executable(DList main.c lib/DList.c lib/DList.h)