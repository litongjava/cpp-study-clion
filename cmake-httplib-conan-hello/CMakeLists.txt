cmake_minimum_required(VERSION 3.23)
project(cmake_httplib_conan_hello)

# 包含由Conan生成的工具链文件
include(conan_toolchain.cmake)

set(CMAKE_CXX_STANDARD 14)

add_executable(cmake_httplib_conan_hello main.cpp)

# 包含由Conan生成的依赖文件
find_package(httplib REQUIRED)
target_link_libraries(my_app httplib::httplib)