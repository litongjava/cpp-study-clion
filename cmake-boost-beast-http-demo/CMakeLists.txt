cmake_minimum_required(VERSION 3.23)
project(cmake_boost_beast_http_demo)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")

find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})
add_executable(boost_version boost_version.cpp ${Boost_LIBRARIES})

add_executable(cmake_boost_beast_http_demo main.cpp boost_version.cpp websocket_session.h)

add_executable(http_server http_server.cpp)

target_link_libraries(http_server jsoncpp Boost::system pthread)