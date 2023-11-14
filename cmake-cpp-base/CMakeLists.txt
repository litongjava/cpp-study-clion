cmake_minimum_required(VERSION 3.25)
project(cmake_cpp_base)

set(CMAKE_CXX_STANDARD 17)

add_executable(cmake_cpp_base main.cpp)
add_executable(print_system_information print_system_information.cpp)
add_executable(dereference_demo dereference_demo.cpp)
