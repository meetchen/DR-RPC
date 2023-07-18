# 设置cmake的最低版本与项目名称
cmake_minimum_required(VERSION 3.0)
project(DR-RPC)

# 设置项目可执行文件的输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 设置项目库文件的输出路径
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# 设置项目编译头文件搜索路径 -I
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/example)

# 设置项目库文件的搜索路径 -L
link_directories(${PROJECT_SOURCE_DIR}/lib)

# add_subdirectory(src)
add_subdirectory(example)