

cmake_minimum_required(VERSION 3.9)
project(sudoku_by_Da)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

set(SOURCE_FILES  main.c)
add_executable(sudoku_by_Da ${SOURCE_FILES})