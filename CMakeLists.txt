cmake_minimum_required(VERSION 3.9)

set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

project(nivlr)

set(SOURCE_FILES src/noctis.cpp src/noctis-1.cpp src/noctis-0.cpp)

add_executable(nivlr ${SOURCE_FILES})
