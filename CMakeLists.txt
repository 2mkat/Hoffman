cmake_minimum_required(VERSION 3.17)
project(hoffman)

set(CMAKE_CXX_STANDARD 14)

add_executable(hoffman helper.h helper.cpp coder.cpp encode.cpp)