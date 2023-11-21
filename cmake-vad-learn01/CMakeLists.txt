cmake_minimum_required(VERSION 3.25)
project(cmake_vad_learn01)

set(CMAKE_CXX_STANDARD 17)
# webrtc
include_directories(webrtc)
# find cpp files
file(GLOB SRC_FILES simplevad/*.c simplevad/*.h
        webrtc/common_audio/*/*.c webrtc/rtc_base/*.c*)

add_executable(main main.cpp ${SRC_FILES})
target_link_libraries(main pthread)