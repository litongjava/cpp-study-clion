cmake_minimum_required(VERSION 3.23)
project(cmake_boost_beast_http_demo)

set(CMAKE_CXX_STANDARD 14)
add_definitions(-D_WIN32_WINNT=0x0601)
if (MSVC)
    add_compile_options(/bigobj)
endif ()
find_package(jsoncpp CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(cmake_boost_beast_http_demo main.cpp)

add_executable(boost_version boost_version.cpp
        http_default_handler.h)
target_link_libraries(boost_version ${Boost_LIBRARIES})

add_executable(http_server http_server.cpp)
target_link_libraries(http_server PRIVATE JsonCpp::JsonCpp ${Boost_LIBRARIES})


