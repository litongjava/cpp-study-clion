cmake_minimum_required(VERSION 3.26)
project(cmake_libmpg123_learn)

set(CMAKE_CXX_STANDARD 17)

find_package(mpg123 CONFIG REQUIRED)
add_executable(libmpg123_ok libmpg123_ok.cpp)
target_link_libraries(libmpg123_ok PRIVATE MPG123::libmpg123 MPG123::libout123 MPG123::libsyn123)

add_executable(cmake_libmpg123_learn main.cpp)
target_link_libraries(cmake_libmpg123_learn PRIVATE MPG123::libmpg123 MPG123::libout123 MPG123::libsyn123)

add_executable(get_mp3_info get_mp3_info.cpp)
target_link_libraries(get_mp3_info PRIVATE MPG123::libmpg123 MPG123::libout123 MPG123::libsyn123)
