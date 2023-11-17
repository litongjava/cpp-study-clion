cmake_minimum_required(VERSION 3.23)
project(cmake_whiser_cpp_demo)

set(CMAKE_CXX_STANDARD 14)

add_executable(cmake_whiser_cpp_demo main.cpp)

# 包含 whisper.cpp 的头文件
include_directories(/mnt/e/code/cpp/project-ping/whisper.cpp)

# 添加 whisper.cpp 库文件所在的目录
link_directories(/mnt/e/code/cpp/project-ping/whisper.cpp/cmake-build-release)

## 创建一个可执行文件
add_executable(demo01 demo01.cpp dr_wav.h common.cpp)

# 链接 whisper.cpp 库
target_link_libraries(demo01 whisper)