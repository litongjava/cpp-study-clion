cmake_minimum_required(VERSION 3.25)
project(cmake_speexdsp_learn)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE speexdsp)



