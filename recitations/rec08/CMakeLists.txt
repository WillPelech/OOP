cmake_minimum_required(VERSION 3.27)
project(rec08)

set(CMAKE_CXX_STANDARD 17)

add_executable(rec08_single rec08_single.cpp)
add_executable(rec08 rec08.cpp registrar.cpp student.cpp course.cpp)
