cmake_minimum_required(VERSION 3.8)

project (assignment)

# set(CMAKE_C_COMPILER "C:/MinGW/bin/gcc.exe")
# set(CMAKE_CXX_COMPILER "C:/MinGW/bin/g++.exe")

include_directories(lib include)
add_compile_options( -DCMAKE_BUILD_TYPE=Debug )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

file(GLOB SOURCES  "tests/SubBinaryTree.cpp")

add_compile_options( -std=gnu++11 )
add_executable( assignment ${SOURCES} )