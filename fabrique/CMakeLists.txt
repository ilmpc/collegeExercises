cmake_minimum_required(VERSION 3.13)
project(Fabrique C)

set(CMAKE_C_STANDARD 11)

add_executable(Fabrique main.c src/circle.h src/circle.c src/new.h src/new.c src/point.c src/point.h src/rect.c src/rect.h src/line.c src/line.h)