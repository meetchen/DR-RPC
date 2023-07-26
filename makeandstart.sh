#!/bin/bash



cd build


if [[ "$1" == "-c" ]]; then
    make clean
    make
elif [[ "$1" == "-rmi" ]]; then
    rm -rf *
    cmake -DCMAKE_VERBOSE_MAKEFILE=ON ..
    make
elif [[ "$1" == "-rm" ]]; then
    rm -rf *
    cmake ..
    make
elif [[ "$1" == "-m" ]]; then
    make
elif [[ "$#" -ne 0 ]]; then
    exit 1
fi



cd ..

./bin/provider -c ./bin/test.conf