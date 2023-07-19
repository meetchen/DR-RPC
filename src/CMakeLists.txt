# 将目录的下的文件都当做 源文件
# 但是. 不会改变，需要清空Makefile重新编译
aux_source_directory(. SRC_LIST)
add_library(drrpc SHARED ${SRC_LIST})