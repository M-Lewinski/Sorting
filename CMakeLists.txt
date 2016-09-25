cmake_minimum_required(VERSION 3.5)
project(Sorting)
aux_source_directory(./src/ SRC_LIST)
aux_source_directory(./src/SelectionSort/ SELECT_SORT)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(SOURCE_FILES main.c)
add_executable(Sorting ${SOURCE_FILES} ${SRC_LIST} ${SELECT_SORT})