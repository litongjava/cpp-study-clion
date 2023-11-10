cmake_minimum_required(VERSION 3.23)
project(cmake_boost_beast_websocket_demo)

set(CMAKE_CXX_STANDARD 14)
# 查找必要的库
find_package(Boost REQUIRED COMPONENTS system)

add_executable(main main.cpp)
add_executable(websocket_server websocket_server.cpp)
# 链接 Boost 库
target_link_libraries(websocket_server Boost::system pthread)