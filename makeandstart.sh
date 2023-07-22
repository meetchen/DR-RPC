#!/bin/bash



cd build


if [[ "$1" == "-c" ]]; then
    make clean
elif [[ "$1" == "-rm" ]]; then
    rm -rf *
    cmake ..
elif [[ "$#" -ne 0 ]]; then
    exit 1
fi

make

cd ..

./bin/provider -c ./bin/test.conf