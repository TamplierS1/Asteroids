#! /bin/bash

if ! test -d build ; then
    mkdir build
fi

cd build

if test -x /usr/bin/clang++; then
    cmake -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
elif test -x clang; then
    cmake -GMake -DCMAKE_CXX_COMPILER=g++ -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
else
    echo "Failed to find any available compilers."
fi

make -j12
cp compile_commands.json ..