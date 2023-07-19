# 将目录的下的文件都当做 源文件
# 但是. 不会改变，需要清空Makefile重新编译
aux_source_directory(. SRC_LIST)
add_library(drrpc ${SRC_LIST})

# 连接muduo库时 先连接net
target_link_libraries(drrpc muduo_net muduo_base pthread)