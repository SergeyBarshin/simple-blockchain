cmake_minimum_required(VERSION 3.7)

project(Simple-Web-Server)

add_library(simple-web-server INTERFACE)

target_include_directories(simple-web-server INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Threads REQUIRED)
target_link_libraries(simple-web-server INTERFACE Threads::Threads)

find_package(Boost COMPONENTS system REQUIRED)
target_link_libraries(simple-web-server INTERFACE Boost::boost Boost::system)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.9)
    target_compile_definitions(simple-web-server INTERFACE USE_BOOST_REGEX)
    find_package(Boost COMPONENTS regex REQUIRED)
    target_link_libraries(simple-web-server INTERFACE Boost::regex)
endif()


if(APPLE)
    if(EXISTS /usr/local/opt/openssl)
        set(OPENSSL_ROOT_DIR /usr/local/opt/openssl)
    elseif(EXISTS /opt/homebrew/opt/openssl)
        set(OPENSSL_ROOT_DIR /opt/homebrew/opt/openssl)
    endif()
endif()
