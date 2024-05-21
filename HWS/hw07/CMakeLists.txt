cmake_minimum_required(VERSION 3.27)
project(hw07)

set(CMAKE_CXX_STANDARD 17)

add_executable(hw07_single hw07-single.cpp )

add_executable(hw07 hw07.cpp Noble.cpp Noble.h Warrior.h Warrior.cpp)
