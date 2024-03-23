cmake_minimum_required(VERSION 3.13)  # CMake version check
set(project simple-blockchain)

project(${project})          
   
set(CMAKE_CXX_STANDARD 20)            # Enable c++20 standard

#add_subdirectory(src)

set(${project}_SOURCES main.cpp)

set(${project}_SOURCE_LIST ${${project}_SOURCES})

add_executable(${project} ${${project}_SOURCE_LIST})
