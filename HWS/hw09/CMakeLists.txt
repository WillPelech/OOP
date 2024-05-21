cmake_minimum_required(VERSION 3.27)
project(hw09)

set(CMAKE_CXX_STANDARD 17)

add_executable(hw09-sing
        hw09-single.cpp)

add_executable(hw09 hw09.cpp
        polynomial.h
        polynomial.cpp
        polynomial.cpp)