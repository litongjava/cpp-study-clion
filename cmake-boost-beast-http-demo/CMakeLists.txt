cmake_minimum_required(VERSION 3.23)
project(cmake_boost_beast_http_demo)

set(CMAKE_CXX_STANDARD 14)

add_executable(cmake_boost_beast_http_demo main.cpp)
add_executable(http_server http_server.cpp)
