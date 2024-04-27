cmake_minimum_required(VERSION 3.25)
project(simplified_tetris)

find_package(Torch REQUIRED)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_executable(simplified_tetris simplified-tetris/main.cpp simplified-tetris/SimplifiedTetris.cpp simplified-tetris/SimplifiedTetris.h)

add_executable(TetrisModelV1 TetrisModelV1/main.cpp TetrisModelV1/TetrisModelV1.cpp TetrisModelV1/TetrisModelV1.h)
target_link_libraries(TetrisModelV1 "${TORCH_LIBRARIES}")
