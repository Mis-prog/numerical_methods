cmake_minimum_required(VERSION 3.27)
project(Lab2)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-O3 -Os)

add_executable(Lab2 src/main.cpp
        src/task1.h
        src/task2.h
        src/task6.h
        src/task3.h
        src/task4.h
        src/task5.h
        src/task5.h

)
