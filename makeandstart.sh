#!/bin/bash

# 此脚本用于执行一系列的Linux命令

# 执行命令：cd build
cd build

# 如果传递了 "-c" 参数，则执行 "make clean"
if [[ "$1" == "-c" ]]; then
    # 执行命令：make clean
    make clean
fi

# 执行命令：make
make

# 执行命令：cd ..
cd ..

# 执行命令：./bin/provider -c ./bin/test.conf
./bin/provider -c ./bin/test.conf
