cmake_minimum_required(VERSION 3.28)
project(simplified_tetris)

set(CMAKE_CXX_STANDARD 17)

add_executable(simplified_tetris simplified-tetris/main.cpp simplified-tetris/SimplifiedTetris.cpp simplified-tetris/SimplifiedTetris.h)

add_executable(TetrisModelV1 TetrisModelV1/main.cpp TetrisModelV1/TetrisModelV1.cpp TetrisModelV1/TetrisModelV1.h)
