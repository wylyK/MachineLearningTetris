cmake_minimum_required(VERSION 3.22)
project(simplified_tetris)

find_package(Torch REQUIRED)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_executable(simplified_tetris simplified-tetris/main.cpp simplified-tetris/SimplifiedTetris.cpp)

add_executable(TetrisModelV1 TetrisModelV1/main.cpp TetrisModelV1/TetrisModelV1.cpp TetrisModelV1/featureExtractor.cpp
        simplified-tetris/SimplifiedTetris.cpp TetrisModelV1/TetrisModelV1Runner.cpp)
target_link_libraries(TetrisModelV1 "${TORCH_LIBRARIES}")
if (MSVC)
    file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
    add_custom_command(TARGET example-app
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${TORCH_DLLS}
            $<TARGET_FILE_DIR:example-app>)
endif (MSVC)