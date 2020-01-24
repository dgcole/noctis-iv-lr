cmake_minimum_required(VERSION 3.9)

project(nivlr)

find_package(SDL2 REQUIRED)
find_library(angelscript REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

set(ANGELSCRIPT_ADDONS src/angelscript_addons/scriptstdstring/scriptstdstring.cpp)

set(SOURCE_FILES src/noctis.cpp src/noctis-1.cpp src/noctis-0.cpp src/brtl.cpp src/scripting.cpp)


add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${ANGELSCRIPT_ADDONS})
target_link_libraries(${PROJECT_NAME} SDL2 angelscript)
