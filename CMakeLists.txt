cmake_minimum_required(VERSION 3.13)
project(nivlr)

set(GODOT_GDEXTENSION_DIR thirdparty/godot-cpp/gdextension/ CACHE STRING "Path to GDExtension interface header directory")
set(GODOT_CPP_BINDINGS_DIR thirdparty/godot-cpp/ CACHE STRING "Path to Godot C++ bindings")

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(TARGET_PATH linux64)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(FATAL_ERROR "No support for ${CMAKE_SYSTEM_NAME}")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(FATAL_ERROR "No support for ${CMAKE_SYSTEM_NAME}")
else()
    message(FATAL_ERROR "No support for ${CMAKE_SYSTEM_NAME}")
endif()

# Change the output directory to the bin directory
set(BUILD_PATH ${CMAKE_SOURCE_DIR}/bin/${TARGET_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BUILD_PATH}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BUILD_PATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_PATH}")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BUILD_PATH}")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BUILD_PATH}")
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BUILD_PATH}")
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BUILD_PATH}")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BUILD_PATH}")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BUILD_PATH}")

# Set the c++ standard to c++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GODOT_COMPILE_FLAGS )
set(GODOT_LINKER_FLAGS )

# Define for using double precision vectors
add_definitions(-DREAL_T_IS_DOUBLE)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # TODO
else()
    set(GODOT_LINKER_FLAGS "-static-libgcc -static-libstdc++ -Wl,-R,'$$ORIGIN'")

    set(GODOT_COMPILE_FLAGS "-fPIC -g -Wwrite-strings")
    # TODO; Re-enable these warnings when possible.
    #set(GODOT_COMPILE_FLAGS "${GODOT_COMPILE_FLAGS} -Wchar-subscripts -Wcomment -Wdisabled-optimization")
    #set(GODOT_COMPILE_FLAGS "${GODOT_COMPILE_FLAGS} -Wformat -Wformat=2 -Wformat-security -Wformat-y2k")
    #set(GODOT_COMPILE_FLAGS "${GODOT_COMPILE_FLAGS} -Wimport -Winit-self -Winline -Winvalid-pch -Werror")
    #set(GODOT_COMPILE_FLAGS "${GODOT_COMPILE_FLAGS} -Wmissing-braces -Wmissing-format-attribute")
    #set(GODOT_COMPILE_FLAGS "${GODOT_COMPILE_FLAGS} -Wmissing-include-dirs -Wmissing-noreturn -Wpacked -Wpointer-arith")
    #set(GODOT_COMPILE_FLAGS "${GODOT_COMPILE_FLAGS} -Wredundant-decls -Wreturn-type -Wsequence-point")
    #set(GODOT_COMPILE_FLAGS "${GODOT_COMPILE_FLAGS} -Wswitch -Wswitch-enum -Wtrigraphs")
    #set(GODOT_COMPILE_FLAGS "${GODOT_COMPILE_FLAGS} -Wuninitialized -Wunknown-pragmas -Wunreachable-code -Wunused-label")
    #set(GODOT_COMPILE_FLAGS "${GODOT_COMPILE_FLAGS} -Wunused-value -Wvariadic-macros -Wvolatile-register-var -Wno-error=attributes")
    #set(GODOT_COMPILE_FLAGS "${GODOT_COMPILE_FLAGS} -Wno-ignored-attributes")

    if(CMAKE_BUILD_TYPE MATCHES Debug)
        set(GODOT_COMPILE_FLAGS "${GODOT_COMPILE_FLAGS} -fno-omit-frame-pointer -O0")
    else()
        set(GODOT_COMPILE_FLAGS "${GODOT_COMPILE_FLAGS} -O3")
    endif(CMAKE_BUILD_TYPE MATCHES Debug)
endif()

# Get Sources
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

# Define shared library
add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} SYSTEM
    PRIVATE
        ${GODOT_CPP_BINDINGS_DIR}/include
        ${GODOT_CPP_BINDINGS_DIR}/gen/include
        ${GODOT_CPP_BINDINGS_DIR}/build/gen/include
        ${GODOT_GDEXTENSION_DIR}
)

# Create the correct name (godot.os.build_type.system_bits)

set(BITS 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(BITS 64)
endif(CMAKE_SIZEOF_VOID_P EQUAL 8)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(GODOT_CPP_BUILD_TYPE Debug)
else()
    set(GODOT_CPP_BUILD_TYPE Release)
endif()

string(TOLOWER ${CMAKE_SYSTEM_NAME} SYSTEM_NAME)
string(TOLOWER ${GODOT_CPP_BUILD_TYPE} BUILD_TYPE)

target_link_directories(${PROJECT_NAME}
    PRIVATE
    ${GODOT_CPP_BINDINGS_DIR}/bin/
)

target_link_libraries(${PROJECT_NAME}
    godot-cpp.${SYSTEM_NAME}.template_${BUILD_TYPE}.double.x86_64
)

# Add the compile flags
set_property(TARGET ${PROJECT_NAME} APPEND_STRING PROPERTY COMPILE_FLAGS ${GODOT_COMPILE_FLAGS})
set_property(TARGET ${PROJECT_NAME} APPEND_STRING PROPERTY LINK_FLAGS ${GODOT_LINKER_FLAGS})

set_property(TARGET ${PROJECT_NAME} PROPERTY OUTPUT_NAME "nivlr")