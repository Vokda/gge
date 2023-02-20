#!/bin/sh

mkdir -p build

rm -rf build/CMake*
rm -f build/cmake*
rm -f build/gge
rm -f Makefile

cmake -B build -DCMAKE_BUILD_TYPE=Debug

cd build
ln -sf ../games/
cd ..
