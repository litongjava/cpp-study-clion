cmake_minimum_required(VERSION 3.25)
project(cmake_speexdsp_learn)

set(CMAKE_CXX_STANDARD 17)
# 查找 SpeexDSP 库
find_library(SPEEXDSP_LIBRARY NAMES speexdsp)
# 查找头文件
find_path(SPEEXDSP_INCLUDE_DIRS "speex/speex_preprocess.h")
add_executable(main main.cpp)
# 链接 SpeexDSP 库
target_link_libraries(main PRIVATE ${SPEEXDSP_LIBRARY})
# 链接头文件
target_include_directories(main PRIVATE ${SPEEXDSP_INCLUDE_DIRS})




