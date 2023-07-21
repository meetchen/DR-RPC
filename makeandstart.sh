#!/bin/bash

# 此脚本用于执行一系列的Linux命令

# 执行命令：cd build
cd build

# 执行命令：make
make clean

make

# 执行命令：cd ..
cd ..

# 执行命令：./bin/provider -c ./bin/test.conf
./bin/provider -c ./bin/test.conf
