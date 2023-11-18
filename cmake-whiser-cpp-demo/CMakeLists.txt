cmake_minimum_required(VERSION 3.23)
project(cmake_whiser_cpp_demo)

set(CMAKE_CXX_STANDARD 14)

add_executable(cmake_whiser_cpp_demo main.cpp)

# 检测操作系统
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    # macOS
    include_directories(/Users/ping/code/cpp/project-litongjava/whisper.cpp)
    link_directories(/Users/ping/code/cpp/project-litongjava/whisper.cpp/cmake-build-release)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # Linux
    include_directories(/mnt/e/code/cpp/project-ping/whisper.cpp)
    link_directories(/mnt/e/code/cpp/project-ping/whisper.cpp/cmake-build-release)
endif()

# 其他 CMake 指令...


## 创建一个可执行文件
add_executable(demo01 demo01.cpp dr_wav.h common.cpp)

# 链接 whisper.cpp 库
target_link_libraries(demo01 whisper)
