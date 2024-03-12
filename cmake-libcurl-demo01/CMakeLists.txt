cmake_minimum_required(VERSION 3.16)
project(libcurl_demo01)

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})
add_executable(libcurl_demo01 main.cpp)
target_link_libraries(libcurl_demo01 ${CURL_LIBRARIES})

