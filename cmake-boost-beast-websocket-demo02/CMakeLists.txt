cmake_minimum_required(VERSION 3.23)
project(cmake_boost_beast_websocket_demo02)

set(CMAKE_CXX_STANDARD 14)
# 查找必要的库
find_package(Boost REQUIRED COMPONENTS system)

add_executable(cmake_boost_beast_websocket_demo02 main.cpp)

add_executable(demo02 demo02.cpp WebSocketServer.cpp Connection.cpp ConnectionMgr.cpp)
target_link_libraries(demo02 Boost::system pthread)
