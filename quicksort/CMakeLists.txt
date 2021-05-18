cmake_minimum_required(VERSION 3.12)
project(QSort C)

set(CMAKE_C_STANDARD 11)

add_executable(QSort main.c src/qsort.c src/qsort.h src/file_sorts.c src/file_sorts.h src/msort.c src/msort.h)