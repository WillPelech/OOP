cmake_minimum_required(VERSION 3.27)
project(hw08)

set(CMAKE_CXX_STANDARD 17)

add_executable(hw08 hw08-single.cpp)

add_executable(hw08-sep hw08.cpp Noble.h Protector.h Protector.cpp Noble.cpp)