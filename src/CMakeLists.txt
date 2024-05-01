cmake_minimum_required(VERSION 3.13)  # CMake version check
set(project simple-blockchain)

project(${project})          
   
set(CMAKE_CXX_STANDARD 20)            # Enable c++20 standard

# Disable building tests and examples in libfort project
set(FORT_ENABLE_TESTING OFF CACHE INTERNAL "")

add_subdirectory(libfort)
add_subdirectory(Simple-Web-Server)
add_subdirectory(core)


# собираем json и веб сервер и линкуем их с core
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(${nlohmann_json_source}
   ${CMAKE_CURRENT_SOURCE_DIR}/json)

find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
target_include_directories(core INTERFACE ${Boost_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/Simple-Web-Server)

target_link_libraries(core PRIVATE simple-web-server nlohmann_json::nlohmann_json /opt/homebrew/opt/openssl/lib/libssl.dylib /opt/homebrew/opt/openssl/lib/libcrypto.dylib ) 

set(${project}_SOURCES main.cpp)
set(${project}_SOURCE_LIST ${${project}_SOURCES})
add_executable(${project} ${${project}_SOURCE_LIST})

#target_link_libraries(${project} OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(${project} PRIVATE fort)
target_link_libraries(${project} PRIVATE core)
