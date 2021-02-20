#! /bin/bash

if ! test -d build ; then
    mkdir build
fi

cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
make -j12
cp compile_commands.json ..