cmake_minimum_required(VERSION 3.5)
project(Sorting)
aux_source_directory(./src/ SRC_LIST)
aux_source_directory(./src/SelectionSort/ SELECT_SORT)
aux_source_directory(./src/InsertionSort/ INSERT_SORT)
aux_source_directory(./src/ShellSort/ SHELL_SORT)
aux_source_directory(./src/HeapSort/ HEAP_SORT)
aux_source_directory(./src/QuickSort/Iterative QUICK_SORT_ITERATIVE)
aux_source_directory(src/QuickSort/Recursive QUICK_SORT_RECURSIVE)


#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")


set(SOURCE_FILES main.c)
add_executable(Sorting ${SOURCE_FILES} ${SRC_LIST} ${SELECT_SORT} ${INSERT_SORT} ${SHELL_SORT} ${HEAP_SORT} ${QUICK_SORT_ITERATIVE} ${QUICK_SORT_RECURSIVE})
target_link_libraries(Sorting m)

