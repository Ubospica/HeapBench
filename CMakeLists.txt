cmake_minimum_required(VERSION 3.16)
SET(CMAKE_CXX_COMPILER /usr/bin/clang++)
project(project)

set(CMAKE_CXX_STANDARD 14)

add_executable(::project main.cpp)