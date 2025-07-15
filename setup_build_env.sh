#!/bin/sh

mkdir -p build

rm -rf build/CMake*
rm -f build/cmake*
rm -f build/gge
rm -f Makefile

# export compilers used (for future)
#export CC=clang
#export CXX=clang++

cmake -B build -DCMAKE_BUILD_TYPE=Debug

cd build
ln -sf ../games/
cd ..
