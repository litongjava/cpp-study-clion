# 指定 vcpkg 的工具链文件（如果您没有在 CLion 设置中指定的话）
cmake_minimum_required(VERSION 3.23)
project(cmake_cpp_httplib_hello)
set(CMAKE_CXX_STANDARD 14)

# 查找 cpp-httplib 包
find_package(httplib CONFIG REQUIRED)

# 添加可执行文件和链接库
add_executable(cmake_cpp_httplib_hello main.cpp)
#add_executable(cmake_cpp_httplib_hello main02.cpp)
target_link_libraries(cmake_cpp_httplib_hello PRIVATE httplib::httplib)

# 添加第二个可执行文件和链接库
add_executable(main02 main02.cpp)
target_link_libraries(main02 PRIVATE httplib::httplib)