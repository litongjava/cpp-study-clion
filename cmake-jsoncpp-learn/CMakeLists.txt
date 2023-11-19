cmake_minimum_required(VERSION 3.23)
project(cmake_jsoncpp_learn)

set(CMAKE_CXX_STANDARD 14)

add_executable(cmake_jsoncpp_learn main.cpp)
add_executable(jsoncpp_demo01 jsoncpp_demo01.cpp)
# 链接 jsoncpp 库
target_link_libraries(jsoncpp_demo01 jsoncpp)