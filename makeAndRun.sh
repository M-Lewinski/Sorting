#!/bin/bash
EXECUTABLE=Sorting
rm -rf build/CMakeCache.txt
cd build
cmake .. && make
./$EXECUTABLE $@

