cmake_minimum_required(VERSION 3.23)
project(cmake_sdl_recoder)

set(CMAKE_CXX_STANDARD 14)

# find SDL2 library
find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
add_executable(main main.cpp common-sdl.h common-sdl.cpp)
# 链接 SDL2 库
target_link_libraries(main ${SDL2_LIBRARIES})