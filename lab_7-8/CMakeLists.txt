cmake_minimum_required(VERSION 3.10)
project(ProcessControlBlock)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(pcb 
    src/main.cpp
    src/ProcessControlBlock.cpp
)

include_directories(src)