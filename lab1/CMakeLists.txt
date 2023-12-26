cmake_minimum_required(VERSION 3.25)
project(Lab1)

set(CMAKE_CXX_STANDARD 17)

set(optimizations "-Ofast")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${optimizations}")

add_executable(Lab1
        src/main.cpp
        src/task1.h
        src/task2.h
        src/task3.h
        src/task4.h
        src/task5.h
        src/task6.h
)
