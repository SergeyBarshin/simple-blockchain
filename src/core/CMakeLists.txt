cmake_minimum_required(VERSION 3.13)  # CMake version check
set(project core)

project(${project})          
   
set(CMAKE_CXX_STANDARD 20)            # Enable c++20 standard

set(${project}_SOURCES Miner.cpp Block.cpp Ledger.cpp Utils.cpp)
set(${project}_HEADERS Miner.hpp MerkleTree.hpp Block.hpp Ledger.hpp Utils.hpp Transaction.hpp Interface.hpp ChatInterface.hpp)


set(${project}_SOURCE_LIST
        ${${project}_SOURCES}
        ${${project}_HEADERS})

add_library(${project}
        STATIC  
        ${${project}_SOURCE_LIST})
