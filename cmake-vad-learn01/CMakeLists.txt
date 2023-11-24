cmake_minimum_required(VERSION 3.25)
project(cmake_vad_learn01)

set(CMAKE_CXX_STANDARD 17)
# webrtc
include_directories(webrtc)
# find cpp files
file(GLOB VAD_FILES simplevad/*.c simplevad/*.h
        webrtc/common_audio/*/*.c webrtc/rtc_base/*.c*)

add_executable(main main.cpp ${VAD_FILES})
target_link_libraries(main pthread)

add_executable(demo01 demo01.cpp ${VAD_FILES})
