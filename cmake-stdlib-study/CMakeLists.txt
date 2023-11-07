cmake_minimum_required(VERSION 3.16)
project(cmake-stdlib-study)

set(CMAKE_CXX_STANDARD 14)

add_executable(main main.cpp)
add_executable(time01 chrono/time01.cpp)
add_executable(hardward01 hardward/hardward01.cpp datatype/int32_t.cpp vector/vector01.cpp)
add_executable(int32_t datatype/int32_t.cpp)
add_executable(vector01.cpp vector/vector01.cpp)