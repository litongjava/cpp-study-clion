cmake_minimum_required(VERSION 3.25)
project(cmake_uWebSockets_demo)

set(CMAKE_CXX_STANDARD 17)

# 查找 uWebSockets 的头文件路径
find_path(UWEBSOCKETS_INCLUDE_DIRS "uwebsockets/App.h")

# 查找 zlib 库
find_package(ZLIB REQUIRED)

# 查找 libuv 库
find_package(libuv CONFIG REQUIRED)
# 查找 uSockets 库
find_library(USOCKETS_LIBRARY uSockets)

add_executable(main main.cpp)

# 链接 uWebSockets、zlib、libuv 和 uSockets 库
target_include_directories(main PRIVATE ${UWEBSOCKETS_INCLUDE_DIRS})
# 检测操作系统
if(WIN32)
    # 如果是 Windows
    target_link_libraries(main PRIVATE ZLIB::ZLIB libuv::uv ${USOCKETS_LIBRARY})
elseif(APPLE)
    # 如果是 MacOS
    target_link_libraries(main PRIVATE ZLIB::ZLIB libuv::uv_a ${USOCKETS_LIBRARY})
else()
    # 对于其他系统，比如 Linux
    target_link_libraries(main PRIVATE ZLIB::ZLIB libuv::uv ${USOCKETS_LIBRARY})
endif()

