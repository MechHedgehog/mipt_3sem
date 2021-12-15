cmake_minimum_required(VERSION 3.21)
project(NEAT)

set(CMAKE_CXX_STANDARD 17)

add_executable(NEAT main.cpp math_util.cpp func.cpp func.h math_util.h attributes.cpp attributes.h activations.cpp activations.h)
