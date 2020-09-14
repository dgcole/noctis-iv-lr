cmake_minimum_required(VERSION 3.9)

project(nivlr)

if (WIN32)
    find_package(SDL2 CONFIG REQUIRED)
else ()
    find_package(SDL2 REQUIRED)
endif ()

include_directories(${SDL2_INCLUDE_DIRS})

set(SOURCE_FILES src/noctis.cpp src/noctis-1.cpp src/noctis-0.cpp src/brtl.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)
else ()
    target_link_libraries(${PROJECT_NAME} SDL2)
endif ()