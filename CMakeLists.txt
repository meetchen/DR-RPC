# 设置cmake的最低版本与项目名称
cmake_minimum_required(VERSION 3.0)
project(DR-RPC)

# 声明 C++ 编译选项，包括调试信息
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# 声明 C 编译选项，包括调试信息
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

# 设置项目可执行文件的输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 设置项目库文件的输出路径
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# 设置项目编译头文件搜索路径 -I
include_directories(${PROJECT_SOURCE_DIR}/src/include)
include_directories(${PROJECT_SOURCE_DIR}/example)

# 设置项目库文件的搜索路径 -L
link_directories(${PROJECT_SOURCE_DIR}/lib)

# src 包含了drrpc框架所有相关代码
add_subdirectory(src)

# example 包含drrpc框架使用的示例代码
add_subdirectory(example)

SET(CMAKE_BUILD_TYPE "Debug")

set (CMAKE_CXX_COMPILER "/usr/bin/g++")

message("C++ Compiler: ${CMAKE_CXX_COMPILER}")

