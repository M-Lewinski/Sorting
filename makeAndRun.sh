#!/bin/bash
rm -rf build/CMakeCache.txt
cd build
cmake .. && make
