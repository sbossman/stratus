cmake_minimum_required(VERSION 3.26)
project(stratus)

set(CMAKE_CXX_STANDARD 17)

add_executable(stratus src/main.cpp
        src/StratusFile.h
        src/StratusFile.cpp
        src/Body.cpp
        src/Head.cpp)
