cmake_minimum_required(VERSION 3.16)
project(freq)

set(CMAKE_CXX_STANDARD 17)

add_executable(freq main.cpp "frequencyParser.cpp" "frequencyParser.h")