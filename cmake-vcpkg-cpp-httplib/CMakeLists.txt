cmake_minimum_required(VERSION 3.23)
project(cmake_vcpkg_cpp_httplib)

set(CMAKE_CXX_STANDARD 17)
find_package(httplib CONFIG REQUIRED)

add_executable(cmake_vcpkg_cpp_httplib main.cpp)
target_link_libraries(cmake_vcpkg_cpp_httplib PRIVATE httplib::httplib)
