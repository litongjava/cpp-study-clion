cmake_minimum_required(VERSION 3.23)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} C)

set(CMAKE_C_STANDARD 99)

# 递归查找当前目录及子目录下的所有 .c 文件
file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

# 生成可执行文件
foreach(file ${SRC_FILES})
    get_filename_component(name ${file} NAME)
    add_executable(${name} ${file} src/for_int_plusplus.c)
endforeach()