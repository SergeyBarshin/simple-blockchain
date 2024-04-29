cmake_minimum_required(VERSION 3.13)  # CMake version check
set(project simple-blockchain)

project(${project})          
   
set(CMAKE_CXX_STANDARD 20)            # Enable c++20 standard

# Disable building tests and examples in libfort project
set(FORT_ENABLE_TESTING OFF CACHE INTERNAL "")

add_subdirectory(libfort)
add_subdirectory(Simple-Web-Server)
add_subdirectory(core)
add_subdirectory(json)

find_package(Boost COMPONENTS system REQUIRED)
target_include_directories(core INTERFACE ${Boost_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/Simple-Web-Server)

target_link_libraries(core PRIVATE simple-web-server)


set(${project}_SOURCES main.cpp)
set(${project}_SOURCE_LIST ${${project}_SOURCES})
add_executable(${project} ${${project}_SOURCE_LIST})

target_link_libraries(${project} PRIVATE fort)
target_link_libraries(${project} PRIVATE core)
target_link_libraries(${project} PRIVATE nlohmann_json)