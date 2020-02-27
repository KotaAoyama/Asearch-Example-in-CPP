cmake_minimum_required(VERSION 3.11.3)

set(CMAKE_CXX_STANDARD 17)

project(AsearchExample)

add_executable(AsearchExample src/A*search.cpp src/1.board)

enable_testing()

add_subdirectory(thirdparty/googletest)