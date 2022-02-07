# CMake bianry version
cmake_minimum_required(VERSION 3.13)

# Proejct info
project(
    ParallelMergeSort
    VERSION 1.0
    DESCRIPTION "Parallel Merge Sort"
)

# CMake bianry version
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

set(APP_NAME sort.out)
set(MAIN_FILE main.cpp)
set(COMPILE_OPTIONS -fopenmp)

add_executable (${APP_NAME} ${MAIN_FILE})
target_compile_options(${APP_NAME} PRIVATE ${COMPILE_OPTIONS})
target_link_options(${APP_NAME} PRIVATE ${COMPILE_OPTIONS})
